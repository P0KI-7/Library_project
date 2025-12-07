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
    inline std::string  getName() const;
    inline std::string& getName();
    inline std::string  getUserID() const;
    inline std::string& getUserID();
    inline std::vector<std::string>  getBorrowBooks() const;
    inline std::vector<std::string>& getBorrowBooks();
    inline int  getMaxBooksAllowed() const;
    inline int& getMaxBooksAllowed();

    bool canBorrowMore();                        // может ли ещё взять книгу
    void addBook(const std::string& isbn); // добавить книгу в список взятых
    void removeBood(const std::string& isbn);      // убрать книгу из списка
    void displayProfile();                    //вывести профиль пользователя
};
#endif //User_h