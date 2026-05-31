#include "TaskManager.h"

#include <exception>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace {
    void clearInput() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    int readMenuChoice() {
        int choice = -1;
        std::cout << "Choose option: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            clearInput();
            throw std::invalid_argument("Invalid menu option.");
        }

        clearInput();
        return choice;
    }

    void showMainMenu() {
        std::cout << "\n====================================\n";
        std::cout << "TASK & PROJECT MANAGER\n";
        std::cout << "====================================\n";
        std::cout << "1. Project Management\n";
        std::cout << "2. Task Management\n";
        std::cout << "3. Search / Filter / Sort\n";
        std::cout << "4. Reports and Statistics\n";
        std::cout << "5. Save Data\n";
        std::cout << "0. Exit\n";
    }
}

int main() {
    TaskManager manager;

    try {
        // Зареждането е при старт, според плана за persistence.
        manager.loadData();
    } catch (const std::exception& error) {
        std::cout << "Warning: " << error.what() << std::endl;
        std::cout << "The program will continue with empty data." << std::endl;
    }

    int choice = -1;

    while (choice != 0) {
        try {
            showMainMenu();
            choice = readMenuChoice();

            switch (choice) {
                case 1:
                    manager.runProjectManagementMenu();
                    break;
                case 2:
                    manager.runTaskManagementMenu();
                    break;
                case 3:
                    manager.runTaskQueryMenu();
                    break;
                case 4:
                    manager.showProjectStatistics();
                    break;
                case 5:
                    manager.saveData();
                    std::cout << "Data saved successfully." << std::endl;
                    break;
                case 0:
                    std::cout << "Exiting program..." << std::endl;
                    break;
                default:
                    std::cout << "Invalid option." << std::endl;
                    break;
            }
        } catch (const std::exception& error) {
            std::cout << "Error: " << error.what() << std::endl;
        }
    }

    return 0;
}
