#include "Book.h"

#include <iostream>

Book::Book()                // Конструктор умолчания
    : title(""), author(""), year(0),\
      isbn(""), isAvailable(true), borrowedBy("")
{
}
// Конструктор общего вида
Book::Book(std::string title, std::string author, int year, \
    std::string isbn, bool isAvailable, std::string borrowedBy) 
    : title(title), author(author), year(year),\
      isbn(isbn), isAvailable(isAvailable), borrowedBy(borrowedBy)
{
}

Book::Book(const Book& other) // Конструктор копирования
    : title(other.title), author(other.author), year(other.year),\
      isbn(other.isbn), isAvailable(other.isAvailable), borrowedBy(other.borrowedBy)
{
}

// Методы для значений
std::string  Book::getTitle()  const {return title;}
std::string& Book::getTitle()        {return title;}
std::string  Book::getAuthor() const {return author;}
std::string& Book::getAuthor()       {return author;}
int  Book::getYear() const {return year;}
int& Book::getYear()       {return year;}
std::string  Book::getIsbn() const {return isbn;}
std::string& Book::getIsbn()       {return isbn;}
bool  Book::getIsAvailable() const {return isAvailable;}
bool& Book::getIsAvailable()       {return isAvailable;}
std::string  Book::getBorrowedBy() const {return borrowedBy;}
std::string& Book::getBorrowedBy()       {return borrowedBy;}
