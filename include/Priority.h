#ifndef PRIORITY_H
#define PRIORITY_H

#include <iosfwd>
#include <string>

enum class Priority {
    Low = 1,
    Medium = 2,
    High = 3,
    Critical = 4
};

std::string priorityToString(Priority priority);
int priorityToInt(Priority priority);
Priority priorityFromInt(int value);
void printPriorityOptions(std::ostream& out);

#endif
