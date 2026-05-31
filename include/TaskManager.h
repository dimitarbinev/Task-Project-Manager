#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include "FileManager.h"

#include <string>
#include <vector>

class TaskManager {
private:
    std::vector<Project> projects;
    FileManager fileManager;
    std::string dataFilePath;

    int findProjectIndexById(int projectId) const;
    Project& getProjectById(int projectId);
    const Project& getProjectById(int projectId) const;

public:
    explicit TaskManager(const std::string& dataFilePath = "data/projects.txt");

    void loadData();
    void saveData() const;

    // Project management
    void addProject();
    void viewAllProjects() const;
    void editProject();
    void deleteProject();

    // Task management
    void addTaskToProject();
    void viewTasksInProject() const;
    void editTaskInProject();
    void deleteTaskFromProject();
    void updateTaskStatus();

    // Search, filter and sort
    void searchTasks() const;
    void filterTasks() const;
    void sortTasks() const;

    // Statistics
    void showProjectStatistics() const;

    // Menus
    void runProjectManagementMenu();
    void runTaskManagementMenu();
    void runTaskQueryMenu() const;
};

#endif
