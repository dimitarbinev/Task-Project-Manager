#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "Project.h"

#include <string>
#include <vector>

class FileManager {
public:
    void saveProjects(const std::string& filePath, const std::vector<Project>& projects) const;
    std::vector<Project> loadProjects(const std::string& filePath) const;
};

#endif
