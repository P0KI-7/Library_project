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
