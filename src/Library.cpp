#include "Library.h"

#include <fstream>
#include <iostream>

Library::Library(std::string dataFile) 
    :dataFile(dataFile), books(), users()
{
    std::string line;
    std::ifstream file(dataFile);

    if(!file.is_open()){
        std::cerr << "Error: Could not open file " << dataFile << std::endl;
        return;
    }

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

// Основной функционал

void Library::addBook(const Book& book)
{
    books.push_back(book);
}

void  Library::addUser(const User& user)
{
    users.push_back(user);
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
    if (tempBook != nullptr && tempUser != nullptr) {
        if ((*tempUser).canBorrowMore()){
            (*tempBook).borrowBook(userName);
            (*tempUser).addBook(isbn);
        }
        else{
            std::cout << "Пользователь не может взять больше книг." << std::endl;
        }
    }
    else if (tempBook == nullptr && tempUser == nullptr) {
        std::cout << "Книга и пользователь не найдены." << std::endl;
    }
    else if (tempBook == nullptr) {
        std::cout << "Книга не найдена." << std::endl;
    }
    else {
        std::cout << "Ползователь не найдена." << std::endl;
    }
}

void  Library::returnBook(const std::string& isbn)
{
    Book* tempBook = findBookByISBN(isbn);
    if (tempBook != nullptr) {
        std::string userName = (*tempBook).getBorrowedBy();
        User* tempUser = findUserByName(userName);
        if (tempUser != nullptr) {
            (*tempBook).returnBook();
            (*tempUser).removeBook(isbn);
        }
        else {
            std::cout << "Незарегистрированный пользователь." << std::endl;
        }
    }
    else {
        std::cout << "Незарегистрированная книга." << std::endl;
    }
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