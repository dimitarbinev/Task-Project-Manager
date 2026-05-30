#include "../include/TaskManager.h"

#include <exception>
#include <iostream>
#include <limits>

namespace {
    void clearInput() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    int readMenuChoice() {
        int choice;

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
        std::cout << std::endl;
        std::cout << "====================================" << std::endl;
        std::cout << "TASK & PROJECT MANAGER" << std::endl;
        std::cout << "====================================" << std::endl;
        std::cout << "1. Create new project" << std::endl;
        std::cout << "2. View all projects" << std::endl;
        std::cout << "3. Edit project" << std::endl;
        std::cout << "4. Delete project" << std::endl;
        std::cout << "0. Exit" << std::endl;
    }
}

int main() {
    TaskManager manager;
    int choice = -1;

    do {
        try {
            showMainMenu();
            choice = readMenuChoice();

            switch (choice) {
                case 1:
                    manager.addProject();
                    break;

                case 2:
                    manager.viewAllProjects();
                    break;

                case 3:
                    manager.editProject();
                    break;

                case 4:
                    manager.deleteProject();
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

    } while (choice != 0);

    return 0;
}