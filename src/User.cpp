#include "User.h"

#include <iostream>

User::User()
    : name(""), userID(""), borrowBooks(), maxBooksAllowed(3)
{
}

User::User(std::string name, std::string userID, \
            std::vector<std::string> borrowBooks, int maxBooksAllowed)
    : name(name), userID(userID), borrowBooks(borrowBooks), maxBooksAllowed(maxBooksAllowed)
{
}

User::User(const User& other)
    : name(other.name), userID(other.userID),\
      borrowBooks(other.borrowBooks), maxBooksAllowed(other.maxBooksAllowed)
{
}

// Методы
std::string  User::getName()  const {return name;}
std::string& User::getName()        {return name;}
std::string  User::getUserID() const {return userID;}
std::string& User::getUserID()       {return userID;}
std::vector<std::string>  User::getBorrowBooks() const {return borrowBooks;};
std::vector<std::string>& User::getBorrowBooks()       {return borrowBooks;}; 
int  User::getMaxBooksAllowed() const {return maxBooksAllowed;};
int& User::getMaxBooksAllowed()       {return maxBooksAllowed;};

// Логика основного функционала

bool User::canBorrowMore()
{
    return (maxBooksAllowed >= borrowBooks.size()+1) ? 1 : 0;
}

void User::addBook(const std::string& isbn)
{
    borrowBooks.push_back(isbn);
}

void User::removeBook(const std::string& isbn)
{
    size_t index = -1;
    for (size_t i = 0; i < borrowBooks.size(); ++i){
        if (borrowBooks[i] == isbn) {
            index = i;
            break;
        }
    }

    if (index != -1){
        borrowBooks.erase(borrowBooks.begin() + index);
    }
    else{
        std::cout << "Эта книга не счислиться у пользователя." << std::endl;
    }
}

void User::displayProfile()
{
    std::cout << "USER" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "UserID: " << userID << std::endl;
    
    size_t i = 0; 
    std::cout << "BorrowedBooks: "<< ((i < borrowBooks.size())?borrowBooks[i++]:"");
    while (i < borrowBooks.size()) {
        std::cout << " | " << borrowBooks[i++];
    }
    std::cout << std::endl;

    std::cout << "MaxBooks: " << maxBooksAllowed << std::endl;
}