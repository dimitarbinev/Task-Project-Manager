#ifndef TASK_H
#define TASK_H

#include "BaseEntity.h"
#include "Priority.h"
#include "TaskStatus.h"

#include <string>

class Task : public BaseEntity {
private:
    std::string title;
    std::string description;
    Date deadline;
    Priority priority;
    TaskStatus status;

public:
    Task();
    Task(const std::string& title,
         const std::string& description,
         const Date& deadline,
         Priority priority,
         TaskStatus status = TaskStatus::NotStarted);
    Task(int id,
         const Date& createdAt,
         const std::string& title,
         const std::string& description,
         const Date& deadline,
         Priority priority,
         TaskStatus status);

    std::string getTitle() const;
    std::string getDescription() const;
    Date getDeadline() const;
    Priority getPriority() const;
    TaskStatus getStatus() const;

    void setTitle(const std::string& title);
    void setDescription(const std::string& description);
    void setDeadline(const Date& deadline);
    void setPriority(Priority priority);
    void setStatus(TaskStatus status);

    bool matchesKeyword(const std::string& keyword) const;

    void displayInfo() const override;
};

#endif
