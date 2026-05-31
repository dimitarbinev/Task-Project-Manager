#include "FileManager.h"

#include <filesystem>
#include <fstream>
#include <iomanip>
#include <stdexcept>

namespace {
    void requireRead(bool condition, const std::string& message) {
        if (!condition) {
            throw std::runtime_error(message);
        }
    }
}

void FileManager::saveProjects(const std::string& filePath, const std::vector<Project>& projects) const {
    const std::filesystem::path outputPath(filePath);
    if (outputPath.has_parent_path()) {
        // Създава липсващите директории преди запис.
        std::filesystem::create_directories(outputPath.parent_path());
    }

    std::ofstream output(filePath);
    if (!output.is_open()) {
        throw std::runtime_error("Could not open file for writing: " + filePath);
    }

    output << projects.size() << '\n';

    for (const Project& project : projects) {
        const Date createdAt = project.getCreatedAt();
        output << "PROJECT "
               << project.getId() << ' '
               << createdAt.getDay() << ' '
               << createdAt.getMonth() << ' '
               << createdAt.getYear() << ' '
               << std::quoted(project.getName()) << ' '
               << std::quoted(project.getDescription()) << ' '
               << project.getTasks().size() << '\n';

        for (const Task& task : project.getTasks()) {
            const Date taskCreatedAt = task.getCreatedAt();
            const Date deadline = task.getDeadline();

            output << "TASK "
                   << task.getId() << ' '
                   << taskCreatedAt.getDay() << ' '
                   << taskCreatedAt.getMonth() << ' '
                   << taskCreatedAt.getYear() << ' '
                   << deadline.getDay() << ' '
                   << deadline.getMonth() << ' '
                   << deadline.getYear() << ' '
                   << priorityToInt(task.getPriority()) << ' '
                   << taskStatusToInt(task.getStatus()) << ' '
                   << std::quoted(task.getTitle()) << ' '
                   << std::quoted(task.getDescription()) << '\n';
        }
    }
}

std::vector<Project> FileManager::loadProjects(const std::string& filePath) const {
    std::ifstream input(filePath);
    if (!input.is_open()) {
        return {};
    }

    std::size_t projectCount = 0;
    requireRead(static_cast<bool>(input >> projectCount), "Invalid file format: missing project count.");

    std::vector<Project> loadedProjects;
    loadedProjects.reserve(projectCount);

    for (std::size_t projectIndex = 0; projectIndex < projectCount; ++projectIndex) {
        std::string projectMarker;
        int projectId = 0;
        int createdDay = 0;
        int createdMonth = 0;
        int createdYear = 0;
        std::string projectName;
        std::string projectDescription;
        std::size_t taskCount = 0;

        requireRead(static_cast<bool>(input >> projectMarker), "Invalid file format: missing PROJECT marker.");
        if (projectMarker != "PROJECT") {
            throw std::runtime_error("Invalid file format: expected PROJECT marker.");
        }

        requireRead(static_cast<bool>(input >> projectId >> createdDay >> createdMonth >> createdYear),
                    "Invalid file format: project header is incomplete.");
        requireRead(static_cast<bool>(input >> std::quoted(projectName) >> std::quoted(projectDescription) >> taskCount),
                    "Invalid file format: project metadata is incomplete.");

        std::vector<Task> tasks;
        tasks.reserve(taskCount);

        for (std::size_t taskIndex = 0; taskIndex < taskCount; ++taskIndex) {
            std::string taskMarker;
            int taskId = 0;
            int taskCreatedDay = 0;
            int taskCreatedMonth = 0;
            int taskCreatedYear = 0;
            int deadlineDay = 0;
            int deadlineMonth = 0;
            int deadlineYear = 0;
            int priorityValue = 0;
            int statusValue = 0;
            std::string title;
            std::string description;

            requireRead(static_cast<bool>(input >> taskMarker), "Invalid file format: missing TASK marker.");
            if (taskMarker != "TASK") {
                throw std::runtime_error("Invalid file format: expected TASK marker.");
            }

            requireRead(static_cast<bool>(input >> taskId
                                               >> taskCreatedDay
                                               >> taskCreatedMonth
                                               >> taskCreatedYear
                                               >> deadlineDay
                                               >> deadlineMonth
                                               >> deadlineYear
                                               >> priorityValue
                                               >> statusValue),
                        "Invalid file format: task header is incomplete.");
            requireRead(static_cast<bool>(input >> std::quoted(title) >> std::quoted(description)),
                        "Invalid file format: task metadata is incomplete.");

            Task task(taskId,
                      Date(taskCreatedDay, taskCreatedMonth, taskCreatedYear),
                      title,
                      description,
                      Date(deadlineDay, deadlineMonth, deadlineYear),
                      priorityFromInt(priorityValue),
                      taskStatusFromInt(statusValue));
            tasks.push_back(task);
        }

        Project project(projectId,
                        Date(createdDay, createdMonth, createdYear),
                        projectName,
                        projectDescription,
                        tasks);
        loadedProjects.push_back(project);
    }

    return loadedProjects;
}
