#include "../include/Project.h"

#include <iostream>
#include <stdexcept>

Project::Project() : BaseEntity(), name("Untitled Project"), description("") {
}

Project::Project(const std::string& name, const std::string& description)
    : BaseEntity() {
    setName(name);
    setDescription(description);
}

std::string Project::getName() const {
    return name;
}

std::string Project::getDescription() const {
    return description;
}

void Project::setName(const std::string& name) {
    if (name.empty()) {
        throw std::invalid_argument("Project name cannot be empty.");
    }

    this->name = name;
}

void Project::setDescription(const std::string& description) {
    this->description = description;
}

void Project::displayInfo() const {
    std::cout << "ID: " << getId() << std::endl;
    std::cout << "Name: " << getName() << std::endl;
    std::cout << "Description: " << getDescription() << std::endl;
    std::cout << "Created at: " << getCreatedAt().toString() << std::endl;
}