#include "Library.h"

#include <fstream>
#include <iostream>

Library::Library(std::string dataFile) 
    :dataFile(dataFile), books(), users()
{
    loadFromFile();
}

// Основной функционал

void Library::addBook(const Book& book)
{
    if (book.getYear() < 1450 || book.getYear() > 2025) {
        throw std::invalid_argument("Некорректный год издания.");
    }
    if (book.getIsbn().empty()) {
      throw std::invalid_argument("ISBN не может быть пустым.");
    }
    
    for (const auto& existingBook : books) {
        if (existingBook.getIsbn() == book.getIsbn()) {
            throw std::runtime_error("Книга с ISBN '" + book.getIsbn() + "' уже существует в библиотеке.");
        }
    }

    books.push_back(book);
    std::cout << "Книга успешна записана." << std::endl;
}

void  Library::addUser(const User& user)
{
    users.push_back(user);
    std::cout << "Пользователь успешно зарегеистрирован." << std::endl;
}

Book* Library::findBookByISBN(const std::string& isbn)
{
    for (size_t i = 0; i < books.size(); ++i) {
        if (books[i].getIsbn() == isbn){
            return &books[i];
        }
    }
    return nullptr;
}

User* Library::findUserByName(const std::string& name)
{
    for (size_t i = 0; i < users.size(); ++i) {
        if (users[i].getName() == name){
            return &users[i];
        }
    }
    return nullptr;
}

void  Library::borrowBook(const std::string& userName, const std::string& isbn)
{
    Book* tempBook = findBookByISBN(isbn);
    User* tempUser = findUserByName(userName);
    
    if (tempBook == nullptr) {
        throw std::runtime_error("Книга с ISBN '" + isbn + "' не найдена.");
    }
    
    if (tempUser == nullptr) {
        throw std::runtime_error("Пользователь '" + userName + "' не найден.");
    }
    
    if (!tempBook->getIsAvailable()) {
        throw std::runtime_error("Книга '" + isbn + "' уже занята.");
    }
    
    if (!tempUser->canBorrowMore()) {
        throw std::runtime_error("Пользователь '" + userName + "' не может взять больше книг.");
    }

    tempBook->borrowBook(userName);
    tempUser->addBook(isbn);
    std::cout << "Книга успешно выдана. Хорошего чтения!" << std::endl;
}

void  Library::returnBook(const std::string& isbn)
{
    Book* book = findBookByISBN(isbn);

    if (!book) {
        throw std::runtime_error("Книга не найдена: " + isbn);
    }
    if (book->getIsAvailable()) {
        throw std::runtime_error("Книга уже доступна");
    }
    std::string userName = book->getBorrowedBy();
    if (userName.empty()) {
        throw std::runtime_error("Не указан пользователь");
    }

    User* user = findUserByName(userName);
    if (!user) throw std::runtime_error("Пользователь не найден: " + userName);
    
    book->returnBook();
    user->removeBook(isbn);
    std::cout << "Книга возвращена успешно. Спасибо, что вернули книгу!" << std::endl;
}

void  Library::displayAllBooks()
{
    std::cout << std::endl;
    for (size_t i = 0; i < books.size(); ++i){
        books[i].displayInfo();
       std::cout << std::endl;
    }
}

void  Library::displayAllUsers()
{
    std::cout << std::endl;
    for (size_t i = 0; i < users.size(); ++i){
        users[i].displayProfile();
       std::cout << std::endl;
    }
}

// Сохранение/загрузка файлов

void  Library::saveToFile()
{
    std::ofstream file(dataFile, std::ios::trunc);

    if(!file.is_open()){
        std::cerr << "Error: Could not open file " << dataFile << std::endl;
        return;
    }

    for (size_t i = 0; i < books.size(); ++i) {
        file << "BOOK" << std::endl;
        file << "Title: " << books[i].getTitle() << std::endl;
        file << "Author: " << books[i].getAuthor() << std::endl;
        file << "Year: " << books[i].getYear() << std::endl;
        file << "ISBN: " << books[i].getIsbn() << std::endl;
        file << "Available: " << (books[i].getIsAvailable() ? "yes" : "no") << std::endl;
        file << "BorrowedBy: " << books[i].getBorrowedBy() << std::endl;
        file << std::endl;
    }

    file << "---USERS---" << std::endl << std::endl;

    for (size_t i = 0; i < users.size(); ++i) {
        file << "USER" << std::endl;
        file << "Name: " << users[i].getName() << std::endl;
        file << "UserID: " << users[i].getUserID() << std::endl;
        
        size_t j = 0; 
        file << "BorrowedBooks: ";
        file << ((j < users[i].getBorrowBooks().size())?users[i].getBorrowBooks()[j++]:"");
        while (j < users[i].getBorrowBooks().size()) {
            file << "|" << users[i].getBorrowBooks()[j++];
        }
        file << std::endl;
        
        file << "MaxBooks: " << users[i].getMaxBooksAllowed() << std::endl;
        file << std::endl;
    }
    
    file.close();
    std::cout << "Data saved to " << dataFile << std::endl;
    std::cout << "Сохранение успешно." << std::endl;
}

void  Library::loadFromFile()
{
    books.clear();
    users.clear();

    std::ifstream file(dataFile);

    if(!file.is_open()){
        std::cerr << "Error: Could not open file " << dataFile << std::endl;
        return;
    }

    std::string line;
    Book tempBook;
    User tempUser;
    bool readingBooks = true;

    while (std::getline(file,line))
    {
        if (line.empty()){
            continue;
        }
        if (line == "---USERS---") {
            readingBooks = false;
            continue;
        }

        if (readingBooks) {
            if (line == "BOOK") {
                if (!tempBook.getTitle().empty()){
                    books.push_back(tempBook);
                }
                tempBook = Book();
                continue;
            }

            size_t colonPos = line.find(":");
            if (colonPos != std::string::npos){
                std::string key = line.substr(0,colonPos);
                std::string value = line.substr(colonPos+2);

                if (key == "Title"){
                    tempBook.getTitle() = value;
                }
                else if (key == "Author"){
                    tempBook.getAuthor() = value; 
                }
                else if (key == "Year"){
                    tempBook.getYear() = std::stoi(value);
                }
                else if (key == "ISBN"){
                    tempBook.getIsbn() = value;
                }
                else if (key == "Available"){
                    if (value == "yes")
                        tempBook.getIsAvailable() = 1;
                    else
                        tempBook.getIsAvailable() = 0;
                }
                else if (key == "BorrowedBy"){
                    tempBook.getBorrowedBy() = value;
                }
            }
        }
        else {
            if (line == "USER"){
                if (!tempUser.getName().empty()){
                    users.push_back(tempUser);
                }
                tempUser = User();
                continue;
            }
            
            size_t colonPos = line.find(":");
            if (colonPos != std::string::npos){
                std::string key = line.substr(0,colonPos);
                std::string value = line.substr(colonPos+2);

                if (key == "Name"){
                    tempUser.getName() = value;
                }
                else if (key == "UserID"){
                    tempUser.getUserID() = value;
                }
                else if (key == "BorrowedBooks"){
                    size_t start = 0;
                    size_t end = value.find('|');
                    
                    while (end != std::string::npos) {
                        std::string isbn = value.substr(start, end - start);
                        if (!isbn.empty()) {
                            tempUser.getBorrowBooks().push_back(isbn);
                        }
                        start = end + 1;
                        end = value.find('|', start);
                    }
                    
                    std::string lastIsbn = value.substr(start);
                    if (!lastIsbn.empty()) {
                        tempUser.getBorrowBooks().push_back(lastIsbn);
                    }
                }
                else if (key == "MaxBooks"){
                    tempUser.getMaxBooksAllowed() = std::stoi(value);
                }
            }
        }
    }

    if (!tempBook.getTitle().empty()) {
        books.push_back(tempBook);
    }
    
    if (!tempUser.getName().empty()){
        users.push_back(tempUser);
    }
    
    file.close();
}
