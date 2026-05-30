#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include "Project.h"
#include <vector>

using namespace std;

class TaskManager {
private:
    vector<Project> projects;

public:
    TaskManager();

    void addProject();
    void viewAllProjects() const;
    void editProject();
    void deleteProject();

    Project* findProjectById(int projectId);
};

#endif