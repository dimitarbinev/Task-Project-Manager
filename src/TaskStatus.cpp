#include "TaskStatus.h"

#include <ostream>
#include <stdexcept>

std::string taskStatusToString(TaskStatus status) {
    switch (status) {
        case TaskStatus::NotStarted:
            return "Not Started";
        case TaskStatus::InProgress:
            return "In Progress";
        case TaskStatus::Completed:
            return "Completed";
        case TaskStatus::Cancelled:
            return "Cancelled";
        default:
            throw std::invalid_argument("Unknown task status value.");
    }
}

int taskStatusToInt(TaskStatus status) {
    return static_cast<int>(status);
}

TaskStatus taskStatusFromInt(int value) {
    switch (value) {
        case 1:
            return TaskStatus::NotStarted;
        case 2:
            return TaskStatus::InProgress;
        case 3:
            return TaskStatus::Completed;
        case 4:
            return TaskStatus::Cancelled;
        default:
            throw std::invalid_argument("Task status must be between 1 and 4.");
    }
}

void printTaskStatusOptions(std::ostream& out) {
    out << "1. Not Started\n"
        << "2. In Progress\n"
        << "3. Completed\n"
        << "4. Cancelled\n";
}
