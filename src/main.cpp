#include "Library.h"
#include "Book.h"

#include <iostream>
#include <windows.h>

void showMenu()
{
    std::cout << "\n=== БИБЛИОТЕКА ===" << std::endl;
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

    try {
        Library MyLibrary = Library("../data/library_data.txt");
        Book tempBook;
        Book* findBook;
        User tempUser;
        User* findUser;
        std::string line;
        std::string line2;
        
        int choice = 0;
        std::string input;
        while (true){
            showMenu();
            std::getline(std::cin,input);

            if (input.empty()) {
                    continue;
            }
            for (char c : input) {
                if (!std::isdigit(static_cast<unsigned char>(c))) {
                    throw std::invalid_argument("Ввод должен содержать только цифры.");
                }
            }

            choice = std::stoi(input);
            
            if (choice == 10) {
                std::cout << "Спасибо за использование библиотеки. До свидания!" << std::endl;
                break;
            }
            
            try {
                switch (choice) {
                case 1:
                    MyLibrary.displayAllBooks();
                    break;
                case 2:
                    MyLibrary.displayAllUsers();
                    break;
                case 3:
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

                    break;
                case 4:
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
                    std::cout << "Пользователь успешно зарегеистрирован." << std::endl;

                    break;
                case 5:
                    std::cout << "Как вас зовут? ";
                    std::getline(std::cin,line);
                    std::cout << "Какую книгу вы хотите взять? Введите её ISBN: ";
                    std::getline(std::cin,line2);
                    MyLibrary.borrowBook(line, line2);
                    break;
                case 6:
                    std::cout << "Как вас зовут? ";
                    std::getline(std::cin,line);
                    std::cout << "Какую книгу вы хотите вернуть? ";
                    std::getline(std::cin,line2);
                    MyLibrary.returnBook(line2);
                    break;
                case 7:
                    std::cout << "Какую книгу вы хотите найти? Введите её ISBN: ";
                    std::getline(std::cin,line);
                    findBook = MyLibrary.findBookByISBN(line);
                    findBook->displayInfo();
                    break;
                case 8:
                    std::cout << "Чей профиль хотите посмотреть? Введите его фамилию: ";
                    std::getline(std::cin,line);
                    findUser = MyLibrary.findUserByName(line);
                    findUser->displayProfile();
                    break;
                case 9:
                    MyLibrary.saveToFile();
                    break;
                default:
                    std::cout << "\nНЕОПОЗНАЯ ОПЦИЯ!" << std::endl;
                    break;
                }
            }
            catch (const std::invalid_argument& e) {
                std::cerr << "Ошибка валидации: " << e.what() << std::endl;
            }
            catch (const std::runtime_error& e) {
                std::cerr << "Ошибка выполнения: " << e.what() << std::endl;
            }
            catch (const std::exception& e) {
                std::cerr << "Неизвестная ошибка: " << e.what() << std::endl;
            }  
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Критическая ошибка при запуске: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}