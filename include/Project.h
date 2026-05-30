#ifndef PROJECT_H
#define PROJECT_H

#include "BaseEntity.h"
#include <string>

using namespace std;

class Project : public BaseEntity {
private:
    string name;
    string description;

public:
    Project();
    Project(const string& name, const string& description);

    string getName() const;
    string getDescription() const;

    void setName(const string& name);
    void setDescription(const string& description);

    void displayInfo() const override;
};

#endif