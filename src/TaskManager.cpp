#include "../include/TaskManager.h"

#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

namespace {
    void clearInput() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    int readInt(const std::string& message) {
        int value;

        std::cout << message;
        std::cin >> value;

        if (std::cin.fail()) {
            clearInput();
            throw std::invalid_argument("Invalid number.");
        }

        clearInput();
        return value;
    }

    std::string readLine(const std::string& message) {
        std::string text;

        std::cout << message;
        std::getline(std::cin, text);

        return text;
    }
}

TaskManager::TaskManager() : projects() {
}

void TaskManager::addProject() {
    std::string name = readLine("Enter project name: ");

    if (name.empty()) {
        throw std::invalid_argument("Project name cannot be empty.");
    }

    std::string description = readLine("Enter project description: ");

    Project project(name, description);
    projects.push_back(project);

    std::cout << "Project created successfully." << std::endl;
}

void TaskManager::viewAllProjects() const {
    if (projects.empty()) {
        std::cout << "No projects available." << std::endl;
        return;
    }

    std::cout << std::endl;
    std::cout << "===== ALL PROJECTS =====" << std::endl;

    for (const Project& project : projects) {
        std::cout << "------------------------" << std::endl;
        project.displayInfo();
    }
}

void TaskManager::editProject() {
    if (projects.empty()) {
        throw std::runtime_error("There are no projects to edit.");
    }

    int projectId = readInt("Enter project ID: ");
    Project* project = findProjectById(projectId);

    if (project == nullptr) {
        throw std::runtime_error("Project not found.");
    }

    std::string newName = readLine("Enter new project name: ");

    if (newName.empty()) {
        throw std::invalid_argument("Project name cannot be empty.");
    }

    std::string newDescription = readLine("Enter new project description: ");

    project->setName(newName);
    project->setDescription(newDescription);

    std::cout << "Project edited successfully." << std::endl;
}

void TaskManager::deleteProject() {
    if (projects.empty()) {
        throw std::runtime_error("There are no projects to delete.");
    }

    int projectId = readInt("Enter project ID: ");

    for (std::size_t i = 0; i < projects.size(); i++) {
        if (projects[i].getId() == projectId) {
            projects.erase(projects.begin() + i);
            std::cout << "Project deleted successfully." << std::endl;
            return;
        }
    }

    throw std::runtime_error("Project not found.");
}

Project* TaskManager::findProjectById(int projectId) {
    for (Project& project : projects) {
        if (project.getId() == projectId) {
            return &project;
        }
    }

    return nullptr;
}