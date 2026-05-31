#include "Project.h"

#include <iostream>
#include <stdexcept>

Project::Project() : BaseEntity(), name("Untitled Project"), description(""), tasks() {
}

Project::Project(const std::string& name, const std::string& description)
    : BaseEntity(), tasks() {
    setName(name);
    setDescription(description);
}

Project::Project(int id,
                 const Date& createdAt,
                 const std::string& name,
                 const std::string& description,
                 const std::vector<Task>& tasks)
    : BaseEntity(id, createdAt), tasks(tasks) {
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

const std::vector<Task>& Project::getTasks() const {
    return tasks;
}

std::vector<Task>& Project::getTasks() {
    return tasks;
}

void Project::setTasks(const std::vector<Task>& tasks) {
    this->tasks = tasks;
}

void Project::addTask(const Task& task) {
    tasks.push_back(task);
}

int Project::findTaskIndexById(int taskId) const {
    for (std::size_t i = 0; i < tasks.size(); ++i) {
        if (tasks[i].getId() == taskId) {
            return static_cast<int>(i);
        }
    }

    return -1;
}

Task& Project::getTaskById(int taskId) {
    const int index = findTaskIndexById(taskId);
    if (index == -1) {
        throw std::runtime_error("Task not found.");
    }

    return tasks[static_cast<std::size_t>(index)];
}

const Task& Project::getTaskById(int taskId) const {
    const int index = findTaskIndexById(taskId);
    if (index == -1) {
        throw std::runtime_error("Task not found.");
    }

    return tasks[static_cast<std::size_t>(index)];
}

void Project::editTask(int taskId,
                       const std::string& title,
                       const std::string& description,
                       const Date& deadline,
                       Priority priority,
                       TaskStatus status) {
    Task& task = getTaskById(taskId);
    task.setTitle(title);
    task.setDescription(description);
    task.setDeadline(deadline);
    task.setPriority(priority);
    task.setStatus(status);
}

void Project::removeTask(int taskId) {
    const int index = findTaskIndexById(taskId);
    if (index == -1) {
        throw std::runtime_error("Task not found.");
    }

    tasks.erase(tasks.begin() + index);
}

int Project::getTaskCount() const {
    return static_cast<int>(tasks.size());
}

int Project::countTasksByStatus(TaskStatus status) const {
    int count = 0;

    for (const Task& task : tasks) {
        if (task.getStatus() == status) {
            ++count;
        }
    }

    return count;
}

double Project::getCompletionRate() const {
    if (tasks.empty()) {
        return 0.0;
    }

    const int completed = countTasksByStatus(TaskStatus::Completed);
    return (static_cast<double>(completed) / static_cast<double>(tasks.size())) * 100.0;
}

void Project::displayInfo() const {
    std::cout << "Project ID: " << getId() << std::endl;
    std::cout << "Name: " << getName() << std::endl;
    std::cout << "Description: " << getDescription() << std::endl;
    std::cout << "Created at: " << getCreatedAt().toString() << std::endl;
    std::cout << "Tasks: " << getTaskCount() << std::endl;
}
