#include "Book.h"
#include "User.h"

#include <string>
#include <stdexcept>

#ifndef Library_h
#define Library_h
class Library{
    std::vector<Book> books; // каталог книг
    std::vector<User> users; // список зарегистрированных пользователей
    std::string dataFile;    // путь к файлу с сохранёнными данными
public:
    Library(std::string dataFile);
    
    void  addBook(const Book& book); // добавить книгу
    void  addUser(const User& user); // зарегистрировать пользователя
    void  borrowBook(const std::string& userName, const std::string& isbn); //выдать книгу пользователю
    void  returnBook(const std::string& isbn);      //принять книгу от пользователя
    Book* findBookByISBN(const std::string& isbn); // найти книгу по ISBN (может вернуть nullptr)
    User* findUserByName(const std::string& name); // найти пользователя по фамилии
    void  displayAllBooks();         // вывести каталог всех книг
    void  displayAllUsers();         // вывести список всех пользователей
    void  saveToFile();              // сохранить состояние библиотеки в файл
    void  loadFromFile();            // загрузить состояние из файла
};
#endif //Library_h