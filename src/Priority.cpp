#include "Priority.h"

#include <ostream>
#include <stdexcept>

std::string priorityToString(Priority priority) {
    switch (priority) {
        case Priority::Low:
            return "Low";
        case Priority::Medium:
            return "Medium";
        case Priority::High:
            return "High";
        case Priority::Critical:
            return "Critical";
        default:
            throw std::invalid_argument("Unknown priority value.");
    }
}

int priorityToInt(Priority priority) {
    return static_cast<int>(priority);
}

Priority priorityFromInt(int value) {
    switch (value) {
        case 1:
            return Priority::Low;
        case 2:
            return Priority::Medium;
        case 3:
            return Priority::High;
        case 4:
            return Priority::Critical;
        default:
            throw std::invalid_argument("Priority must be between 1 and 4.");
    }
}

void printPriorityOptions(std::ostream& out) {
    out << "1. Low\n"
        << "2. Medium\n"
        << "3. High\n"
        << "4. Critical\n";
}
