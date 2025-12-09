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

void Library::addBook(const Book& book)
{
    books.push_back(book);
}

void  Library::addUser(const User& user)
{
    users.push_back(user);
}

