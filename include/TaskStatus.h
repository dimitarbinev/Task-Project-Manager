#ifndef TASK_STATUS_H
#define TASK_STATUS_H

#include <iosfwd>
#include <string>

enum class TaskStatus {
    NotStarted = 1,
    InProgress = 2,
    Completed = 3,
    Cancelled = 4
};

std::string taskStatusToString(TaskStatus status);
int taskStatusToInt(TaskStatus status);
TaskStatus taskStatusFromInt(int value);
void printTaskStatusOptions(std::ostream& out);

#endif
