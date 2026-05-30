#ifndef BASE_ENTITY_H
#define BASE_ENTITY_H

#include "Date.h"

class BaseEntity {
protected:
    int id;
    Date createdAt;

private:
    static int nextId;

public:
    BaseEntity();

    int getId() const;
    Date getCreatedAt() const;

    virtual void displayInfo() const = 0;

    virtual ~BaseEntity();
};

#endif