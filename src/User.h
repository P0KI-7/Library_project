#include <string>
#include <vector>

#ifndef User_h
#define User_h
class User {
    std::string name;                                  // фамилия пользователя
    std::string userID;                      // уникальный ID (вида "USR_001")
    std::vector<std::string> borrowBooks;          //список ISBN выданных книг
    int maxBooksAllowed; //максимум книг, которые может взять (по умолчанию 3)
public:
    // Конструкторы
    User();
    User(std::string name,std::string userID,\
        std::vector<std::string> borrowBooks,int maxBooksAllowed);
    User(const User& other);

    // Методы
    std::string  getName() const;
    std::string& getName();
    std::string  getUserID() const;
    std::string& getUserID();
    std::vector<std::string>  getBorrowBooks() const;
    std::vector<std::string>& getBorrowBooks();
    int  getMaxBooksAllowed() const;
    int& getMaxBooksAllowed();

    bool canBorrowMore();                        // может ли ещё взять книгу
    void addBook(const std::string& isbn); // добавить книгу в список взятых
    void removeBook(const std::string& isbn);      // убрать книгу из списка
    void displayProfile();                    //вывести профиль пользователя
};
#endif //User_h