#include "TaskManager.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
    void clearInput() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Централизирано четене на int, за да не се смесват повредени потоци и getline().
    int readInt(const std::string& message) {
        int value = 0;
        std::cout << message;
        std::cin >> value;

        if (std::cin.fail()) {
            clearInput();
            throw std::invalid_argument("Invalid number.");
        }

        clearInput();
        return value;
    }

    std::string readLine(const std::string& message) {
        std::string text;
        std::cout << message;
        std::getline(std::cin, text);
        return text;
    }

    std::string readNonEmptyLine(const std::string& message, const std::string& errorMessage) {
        const std::string text = readLine(message);
        if (text.empty()) {
            throw std::invalid_argument(errorMessage);
        }
        return text;
    }

    Date readDate(const std::string& message) {
        const std::string text = readNonEmptyLine(message, "Date cannot be empty.");
        return Date::parse(text);
    }

    Priority readPriority() {
        std::cout << "Choose priority:\n";
        printPriorityOptions(std::cout);
        return priorityFromInt(readInt("Option: "));
    }

    TaskStatus readTaskStatus() {
        std::cout << "Choose task status:\n";
        printTaskStatusOptions(std::cout);
        return taskStatusFromInt(readInt("Option: "));
    }

    // Демонстрация на полиморфизъм през базов клас.
    void displayEntity(const BaseEntity& entity) {
        entity.displayInfo();
    }

    struct TaskSnapshot {
        std::string projectName;
        int projectId;
        Task task;
    };

    std::vector<TaskSnapshot> collectAllTasks(const std::vector<Project>& projects) {
        std::vector<TaskSnapshot> result;
        for (const Project& project : projects) {
            for (const Task& task : project.getTasks()) {
                result.push_back({project.getName(), project.getId(), task});
            }
        }
        return result;
    }

    void printTaskWithProjectContext(const TaskSnapshot& snapshot) {
        std::cout << "Project: " << snapshot.projectName
                  << " (ID: " << snapshot.projectId << ")" << std::endl;
        displayEntity(snapshot.task);
    }
}

TaskManager::TaskManager(const std::string& dataFilePath)
    : projects(), fileManager(), dataFilePath(dataFilePath) {
}

void TaskManager::loadData() {
    projects = fileManager.loadProjects(dataFilePath);
}

void TaskManager::saveData() const {
    fileManager.saveProjects(dataFilePath, projects);
}

int TaskManager::findProjectIndexById(int projectId) const {
    for (std::size_t i = 0; i < projects.size(); ++i) {
        if (projects[i].getId() == projectId) {
            return static_cast<int>(i);
        }
    }

    return -1;
}

Project& TaskManager::getProjectById(int projectId) {
    const int index = findProjectIndexById(projectId);
    if (index == -1) {
        throw std::runtime_error("Project not found.");
    }

    return projects[static_cast<std::size_t>(index)];
}

const Project& TaskManager::getProjectById(int projectId) const {
    const int index = findProjectIndexById(projectId);
    if (index == -1) {
        throw std::runtime_error("Project not found.");
    }

    return projects[static_cast<std::size_t>(index)];
}

void TaskManager::addProject() {
    const std::string name = readNonEmptyLine("Enter project name: ", "Project name cannot be empty.");
    const std::string description = readLine("Enter project description: ");

    projects.push_back(Project(name, description));
    std::cout << "Project created successfully." << std::endl;
}

void TaskManager::viewAllProjects() const {
    if (projects.empty()) {
        std::cout << "No projects available." << std::endl;
        return;
    }

    std::cout << "\n===== ALL PROJECTS =====" << std::endl;
    for (const Project& project : projects) {
        std::cout << "------------------------" << std::endl;
        displayEntity(project);
    }
}

void TaskManager::editProject() {
    if (projects.empty()) {
        throw std::runtime_error("There are no projects to edit.");
    }

    const int projectId = readInt("Enter project ID: ");
    Project& project = getProjectById(projectId);

    const std::string newName = readNonEmptyLine("Enter new project name: ", "Project name cannot be empty.");
    const std::string newDescription = readLine("Enter new project description: ");

    project.setName(newName);
    project.setDescription(newDescription);

    std::cout << "Project edited successfully." << std::endl;
}

void TaskManager::deleteProject() {
    if (projects.empty()) {
        throw std::runtime_error("There are no projects to delete.");
    }

    const int projectId = readInt("Enter project ID: ");
    const int index = findProjectIndexById(projectId);

    if (index == -1) {
        throw std::runtime_error("Project not found.");
    }

    projects.erase(projects.begin() + index);
    std::cout << "Project deleted successfully." << std::endl;
}

void TaskManager::addTaskToProject() {
    if (projects.empty()) {
        throw std::runtime_error("Create a project before adding tasks.");
    }

    const int projectId = readInt("Enter project ID: ");
    Project& project = getProjectById(projectId);

    const std::string title = readNonEmptyLine("Enter task title: ", "Task title cannot be empty.");
    const std::string description = readLine("Enter task description: ");
    const Date deadline = readDate("Enter deadline (dd.mm.yyyy): ");
    const Priority priority = readPriority();

    project.addTask(Task(title, description, deadline, priority));
    std::cout << "Task added successfully." << std::endl;
}

void TaskManager::viewTasksInProject() const {
    if (projects.empty()) {
        std::cout << "No projects available." << std::endl;
        return;
    }

    const int projectId = readInt("Enter project ID: ");
    const Project& project = getProjectById(projectId);

    std::cout << "\n===== PROJECT TASKS =====" << std::endl;
    std::cout << "Project: " << project.getName() << std::endl;

    if (project.getTasks().empty()) {
        std::cout << "No tasks in this project." << std::endl;
        return;
    }

    for (const Task& task : project.getTasks()) {
        std::cout << "------------------------" << std::endl;
        displayEntity(task);
    }
}

void TaskManager::editTaskInProject() {
    if (projects.empty()) {
        throw std::runtime_error("No projects available.");
    }

    const int projectId = readInt("Enter project ID: ");
    Project& project = getProjectById(projectId);

    if (project.getTasks().empty()) {
        throw std::runtime_error("This project has no tasks to edit.");
    }

    const int taskId = readInt("Enter task ID: ");
    const std::string title = readNonEmptyLine("Enter new task title: ", "Task title cannot be empty.");
    const std::string description = readLine("Enter new task description: ");
    const Date deadline = readDate("Enter new deadline (dd.mm.yyyy): ");
    const Priority priority = readPriority();
    const TaskStatus status = readTaskStatus();

    project.editTask(taskId, title, description, deadline, priority, status);
    std::cout << "Task edited successfully." << std::endl;
}

void TaskManager::deleteTaskFromProject() {
    if (projects.empty()) {
        throw std::runtime_error("No projects available.");
    }

    const int projectId = readInt("Enter project ID: ");
    Project& project = getProjectById(projectId);

    if (project.getTasks().empty()) {
        throw std::runtime_error("This project has no tasks to delete.");
    }

    const int taskId = readInt("Enter task ID: ");
    project.removeTask(taskId);
    std::cout << "Task deleted successfully." << std::endl;
}

void TaskManager::updateTaskStatus() {
    if (projects.empty()) {
        throw std::runtime_error("No projects available.");
    }

    const int projectId = readInt("Enter project ID: ");
    Project& project = getProjectById(projectId);

    if (project.getTasks().empty()) {
        throw std::runtime_error("This project has no tasks to update.");
    }

    const int taskId = readInt("Enter task ID: ");
    Task& task = project.getTaskById(taskId);
    task.setStatus(readTaskStatus());

    std::cout << "Task status updated successfully." << std::endl;
}

void TaskManager::searchTasks() const {
    const std::string keyword = readNonEmptyLine("Enter keyword to search: ", "Keyword cannot be empty.");
    const std::vector<TaskSnapshot> allTasks = collectAllTasks(projects);

    bool found = false;
    for (const TaskSnapshot& snapshot : allTasks) {
        if (snapshot.task.matchesKeyword(keyword)) {
            if (!found) {
                std::cout << "\n===== SEARCH RESULTS =====" << std::endl;
            }
            std::cout << "------------------------" << std::endl;
            printTaskWithProjectContext(snapshot);
            found = true;
        }
    }

    if (!found) {
        std::cout << "No tasks matched your search." << std::endl;
    }
}

void TaskManager::filterTasks() const {
    if (projects.empty()) {
        std::cout << "No projects available." << std::endl;
        return;
    }

    const int filterOption = readInt("Filter by: 1. Status  2. Priority\nOption: ");
    const std::vector<TaskSnapshot> allTasks = collectAllTasks(projects);
    bool found = false;

    std::cout << "\n===== FILTER RESULTS =====" << std::endl;

    if (filterOption == 1) {
        const TaskStatus targetStatus = readTaskStatus();
        for (const TaskSnapshot& snapshot : allTasks) {
            if (snapshot.task.getStatus() == targetStatus) {
                std::cout << "------------------------" << std::endl;
                printTaskWithProjectContext(snapshot);
                found = true;
            }
        }
    } else if (filterOption == 2) {
        const Priority targetPriority = readPriority();
        for (const TaskSnapshot& snapshot : allTasks) {
            if (snapshot.task.getPriority() == targetPriority) {
                std::cout << "------------------------" << std::endl;
                printTaskWithProjectContext(snapshot);
                found = true;
            }
        }
    } else {
        throw std::invalid_argument("Invalid filter option.");
    }

    if (!found) {
        std::cout << "No tasks matched the selected filter." << std::endl;
    }
}

void TaskManager::sortTasks() const {
    if (projects.empty()) {
        std::cout << "No projects available." << std::endl;
        return;
    }

    std::vector<TaskSnapshot> allTasks = collectAllTasks(projects);
    if (allTasks.empty()) {
        std::cout << "No tasks available." << std::endl;
        return;
    }

    const int sortOption = readInt("Sort by: 1. Deadline  2. Priority\nOption: ");

    if (sortOption == 1) {
        std::sort(allTasks.begin(), allTasks.end(), [](const TaskSnapshot& left, const TaskSnapshot& right) {
            return left.task.getDeadline() < right.task.getDeadline();
        });
    } else if (sortOption == 2) {
        std::sort(allTasks.begin(), allTasks.end(), [](const TaskSnapshot& left, const TaskSnapshot& right) {
            const int leftPriority = priorityToInt(left.task.getPriority());
            const int rightPriority = priorityToInt(right.task.getPriority());

            if (leftPriority != rightPriority) {
                return leftPriority > rightPriority; // По-високият приоритет излиза първи.
            }

            return left.task.getDeadline() < right.task.getDeadline();
        });
    } else {
        throw std::invalid_argument("Invalid sort option.");
    }

    std::cout << "\n===== SORTED TASKS =====" << std::endl;
    for (const TaskSnapshot& snapshot : allTasks) {
        std::cout << "------------------------" << std::endl;
        printTaskWithProjectContext(snapshot);
    }
}

void TaskManager::showProjectStatistics() const {
    if (projects.empty()) {
        std::cout << "No projects available." << std::endl;
        return;
    }

    const int projectId = readInt("Enter project ID: ");
    const Project& project = getProjectById(projectId);

    std::cout << "\n===== PROJECT STATISTICS =====" << std::endl;
    std::cout << "Project: " << project.getName() << std::endl;
    std::cout << "Total tasks: " << project.getTaskCount() << std::endl;
    std::cout << "Not started: " << project.countTasksByStatus(TaskStatus::NotStarted) << std::endl;
    std::cout << "In progress: " << project.countTasksByStatus(TaskStatus::InProgress) << std::endl;
    std::cout << "Completed: " << project.countTasksByStatus(TaskStatus::Completed) << std::endl;
    std::cout << "Cancelled: " << project.countTasksByStatus(TaskStatus::Cancelled) << std::endl;
    std::cout << std::fixed << std::setprecision(2)
              << "Completion rate: " << project.getCompletionRate() << "%" << std::endl;
}

void TaskManager::runProjectManagementMenu() {
    int choice = -1;

    while (choice != 0) {
        std::cout << "\n===== PROJECT MANAGEMENT =====" << std::endl;
        std::cout << "1. Create project" << std::endl;
        std::cout << "2. View all projects" << std::endl;
        std::cout << "3. Edit project" << std::endl;
        std::cout << "4. Delete project" << std::endl;
        std::cout << "0. Back" << std::endl;

        try {
            choice = readInt("Choose option: ");

            switch (choice) {
                case 1:
                    addProject();
                    break;
                case 2:
                    viewAllProjects();
                    break;
                case 3:
                    editProject();
                    break;
                case 4:
                    deleteProject();
                    break;
                case 0:
                    break;
                default:
                    std::cout << "Invalid option." << std::endl;
                    break;
            }
        } catch (const std::exception& error) {
            std::cout << "Error: " << error.what() << std::endl;
        }
    }
}

void TaskManager::runTaskManagementMenu() {
    int choice = -1;

    while (choice != 0) {
        std::cout << "\n===== TASK MANAGEMENT =====" << std::endl;
        std::cout << "1. Add task to project" << std::endl;
        std::cout << "2. View tasks in project" << std::endl;
        std::cout << "3. Edit task" << std::endl;
        std::cout << "4. Delete task" << std::endl;
        std::cout << "5. Update task status" << std::endl;
        std::cout << "0. Back" << std::endl;

        try {
            choice = readInt("Choose option: ");

            switch (choice) {
                case 1:
                    addTaskToProject();
                    break;
                case 2:
                    viewTasksInProject();
                    break;
                case 3:
                    editTaskInProject();
                    break;
                case 4:
                    deleteTaskFromProject();
                    break;
                case 5:
                    updateTaskStatus();
                    break;
                case 0:
                    break;
                default:
                    std::cout << "Invalid option." << std::endl;
                    break;
            }
        } catch (const std::exception& error) {
            std::cout << "Error: " << error.what() << std::endl;
        }
    }
}

void TaskManager::runTaskQueryMenu() const {
    int choice = -1;

    while (choice != 0) {
        std::cout << "\n===== SEARCH / FILTER / SORT =====" << std::endl;
        std::cout << "1. Search tasks by keyword" << std::endl;
        std::cout << "2. Filter tasks" << std::endl;
        std::cout << "3. Sort tasks" << std::endl;
        std::cout << "0. Back" << std::endl;

        try {
            choice = readInt("Choose option: ");

            switch (choice) {
                case 1:
                    searchTasks();
                    break;
                case 2:
                    filterTasks();
                    break;
                case 3:
                    sortTasks();
                    break;
                case 0:
                    break;
                default:
                    std::cout << "Invalid option." << std::endl;
                    break;
            }
        } catch (const std::exception& error) {
            std::cout << "Error: " << error.what() << std::endl;
        }
    }
}
