#ifndef PROJECT_H
#define PROJECT_H

#include "BaseEntity.h"
#include "Task.h"

#include <vector>
#include <string>

class Project : public BaseEntity {
private:
    std::string name;
    std::string description;
    std::vector<Task> tasks;

    int findTaskIndexById(int taskId) const;

public:
    Project();
    Project(const std::string& name, const std::string& description);
    Project(int id,
            const Date& createdAt,
            const std::string& name,
            const std::string& description,
            const std::vector<Task>& tasks);

    std::string getName() const;
    std::string getDescription() const;

    void setName(const std::string& name);
    void setDescription(const std::string& description);

    const std::vector<Task>& getTasks() const;
    std::vector<Task>& getTasks();
    void setTasks(const std::vector<Task>& tasks);

    void addTask(const Task& task);
    void editTask(int taskId,
                  const std::string& title,
                  const std::string& description,
                  const Date& deadline,
                  Priority priority,
                  TaskStatus status);
    void removeTask(int taskId);

    Task& getTaskById(int taskId);
    const Task& getTaskById(int taskId) const;

    int getTaskCount() const;
    int countTasksByStatus(TaskStatus status) const;
    double getCompletionRate() const;

    void displayInfo() const override;
};

#endif
