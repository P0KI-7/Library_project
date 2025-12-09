#include "Library.h"
#include "Book.h"

#include <iostream>
#include <windows.h>

void showMenu()
{
    std::cout << "=== БИБЛИОТЕКА ===" << std::endl;
    std::cout << "1. Просмотреть все книги" << std::endl;
    std::cout << "2. Просмотреть всех пользователей" << std::endl;
    std::cout << "3. Добавить новую книгу" << std::endl;
    std::cout << "4. Зарегистрировать пользователя" << std::endl;
    std::cout << "5. Выдать книгу пользователю" << std::endl;
    std::cout << "6. Принять книгу от пользователя" << std::endl;
    std::cout << "7. Поиск книги по ISBN" << std::endl;
    std::cout << "8. Просмотреть профиль пользователя" << std::endl;
    std::cout << "9. Сохранить данные в файл" << std::endl;
    std::cout << "10. Выход" << std::endl;
    std::cout << "Ваш выбор: ";
}

int main()
{
    // Переключаем консоль в UTF-8
    SetConsoleOutputCP(65001); 
    SetConsoleCP(65001);

    Library MyLibrary = Library("../data/library_data.txt");
    Book tempBook;
    Book* findBook;
    User tempUser;
    User* findUser;
    std::string line;
    std::string line2;
    
    int choice = 0;
    showMenu();
    std::cin >> choice;
    while (choice != 10){
        switch (choice) {
        case 1:
            MyLibrary.displayAllBooks();
            break;
        case 2:
            MyLibrary.displayAllUsers();
            break;
        case 3:
            std::cin.ignore();
            tempBook = Book();
            std::cout << "Заполинет данные о книге." << std::endl;
            
            std::cout << "Title: ";
            std::getline(std::cin,line);
            tempBook.getTitle() = line;
            std::cout << "Author: ";
            std::getline(std::cin,line);
            tempBook.getAuthor() = line;
            std::cout << "Year: ";
            std::getline(std::cin,line);
            tempBook.getYear() = std::stoi(line);
            std::cout << "ISBN: ";
            std::getline(std::cin,line);
            tempBook.getIsbn() = line;
            std::cout << "Available (yes/no): ";
            std::getline(std::cin,line);
            tempBook.getIsAvailable() = (line=="yes") ? 1:0;
            if (line == "no"){
                std::cout << "BorrowedBy: ";
                std::getline(std::cin,line);
                tempBook.getBorrowedBy() = line;
            }
            MyLibrary.addBook(tempBook);
            std::cout << "Книга успешна записана." << std::endl << std::endl;
            
            break;
        case 4:
            std::cin.ignore();
            tempUser = User();
            std::cout << "Заполинет данные о пользователе." << std::endl;
            
            std::cout << "Name: ";
            std::getline(std::cin,line);
            tempUser.getName() = line;
            std::cout << "UserID: ";
            std::getline(std::cin,line);
            tempUser.getUserID() = line;
            std::cout << "Если книги в пользовании (yes/no)? ";
            std::cin >> line;
            if (line == "yes") {
                std::cout << "Сколько их? ";
                int count;
                std::cin >> count;
                std::cout << "Введите каждую книгу в отдельной строчке:" << std::endl;
                for (int i = 0; i < count; ++i) {
                    std::cin.ignore();
                    std::getline(std::cin,line);
                    tempUser.getBorrowBooks().push_back(line);
                }
            }
            MyLibrary.addUser(tempUser);
            std::cout << "Пользователь успешно зарегеистрирован." << std::endl << std::endl;

            break;
        case 5:
            std::cin.ignore();

            std::cout << "Как вас зовут? ";
            std::getline(std::cin,line);
            std::cout << "Какую книгу вы хотите взять? ";
            std::getline(std::cin,line2);
            MyLibrary.borrowBook(line, line2);
            std::cout << "Удачного чтения!" << std::endl << std::endl;

            break;
        case 6:
            std::cin.ignore();

            std::cout << "Как вас зовут? ";
            std::getline(std::cin,line);
            std::cout << "Какую книгу вы хотите вернуть? ";
            std::getline(std::cin,line2);
            MyLibrary.returnBook(line2);
            std::cout << "Спасибо, что вернули книгу!" << std::endl << std::endl;

            break;
        case 7:
            std::cin.ignore();

            std::cout << "Какую книгу вы хотите найти? Введите её ISBN: ";
            std::getline(std::cin,line);
            findBook = MyLibrary.findBookByISBN(line);
            (*findBook).displayInfo();
            std::cout << std::endl;

            break;
        case 8:
            std::cin.ignore();

            std::cout << "Чей профиль хотите посмотреть? Введите его фамилию: ";
            std::getline(std::cin,line);
            findUser = MyLibrary.findUserByName(line);
            (*findUser).displayProfile();
            std::cout << std::endl;

            break;
        case 9:
            MyLibrary.saveToFile();
            std::cout << "Сохранение успешно." << std::endl << std::endl;

            break;
        default:
            std::cout << "Неопозная опция." << std::endl << std::endl;

            break;
        }
        
        showMenu();
        std::cin >> choice;
    }

    return 0;
}