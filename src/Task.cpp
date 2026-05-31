#include "Task.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <stdexcept>

namespace {
    std::string toLowerCopy(std::string text) {
        std::transform(text.begin(), text.end(), text.begin(), [](unsigned char ch) {
            return static_cast<char>(std::tolower(ch));
        });
        return text;
    }
}

Task::Task()
    : BaseEntity(),
      title("Untitled Task"),
      description(""),
      deadline(Date::today()),
      priority(Priority::Medium),
      status(TaskStatus::NotStarted) {
}

Task::Task(const std::string& title,
           const std::string& description,
           const Date& deadline,
           Priority priority,
           TaskStatus status)
    : BaseEntity(), deadline(deadline), priority(priority), status(status) {
    setTitle(title);
    setDescription(description);
}

Task::Task(int id,
           const Date& createdAt,
           const std::string& title,
           const std::string& description,
           const Date& deadline,
           Priority priority,
           TaskStatus status)
    : BaseEntity(id, createdAt), deadline(deadline), priority(priority), status(status) {
    setTitle(title);
    setDescription(description);
}

std::string Task::getTitle() const {
    return title;
}

std::string Task::getDescription() const {
    return description;
}

Date Task::getDeadline() const {
    return deadline;
}

Priority Task::getPriority() const {
    return priority;
}

TaskStatus Task::getStatus() const {
    return status;
}

void Task::setTitle(const std::string& title) {
    if (title.empty()) {
        throw std::invalid_argument("Task title cannot be empty.");
    }

    this->title = title;
}

void Task::setDescription(const std::string& description) {
    this->description = description;
}

void Task::setDeadline(const Date& deadline) {
    this->deadline = deadline;
}

void Task::setPriority(Priority priority) {
    this->priority = priority;
}

void Task::setStatus(TaskStatus status) {
    this->status = status;
}

bool Task::matchesKeyword(const std::string& keyword) const {
    if (keyword.empty()) {
        return false;
    }

    const std::string lowerKeyword = toLowerCopy(keyword);
    const std::string lowerTitle = toLowerCopy(title);
    const std::string lowerDescription = toLowerCopy(description);

    return lowerTitle.find(lowerKeyword) != std::string::npos
        || lowerDescription.find(lowerKeyword) != std::string::npos;
}

void Task::displayInfo() const {
    std::cout << "Task ID: " << getId() << std::endl;
    std::cout << "Title: " << getTitle() << std::endl;
    std::cout << "Description: " << getDescription() << std::endl;
    std::cout << "Created at: " << getCreatedAt().toString() << std::endl;
    std::cout << "Deadline: " << getDeadline().toString() << std::endl;
    std::cout << "Priority: " << priorityToString(getPriority()) << std::endl;
    std::cout << "Status: " << taskStatusToString(getStatus()) << std::endl;
}
