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