#include <string>

#ifndef Book_h
#define Book_h
class Book {
    // Поля (private)
    std::string title;      //название книги
    std::string author;     //автор
    int year;               //год издания
    std::string isbn;       //уникальный ISBN
    bool isAvailable;       //доступна ли книга для выдачи
    std::string borrowedBy;//фамилия пользователя, взявшего книгу
public:
    // Конструкторы
    Book();
    Book(std::string title, std::string author,int year, \
      std::string isbn, bool isAvailable, std:: string borrowedBy);
    Book(const Book& other);

    // Методы
    inline std::string  getTitle() const;
    inline std::string& getTitle();
    inline std::string  getAuthor() const;
    inline std::string& getAuthor();
    inline int  getYear() const;
    inline int& getYear();
    inline std::string  getIsbn() const;
    inline std::string& getIsbn();
    inline bool  getIsAvailable() const;
    inline bool& getIsAvailable();
    inline std::string  getBorrowedBy() const;
    inline std::string& getBorrowedBy();

    void borrowBook(const std::string& userName);//выдыть книгу
    void returnBook();                          //вернуть книгу 
    void displayInfo();  //вывести информацию о книгк в консоль
};
#endif // Book_h