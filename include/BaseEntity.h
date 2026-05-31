#ifndef BASE_ENTITY_H
#define BASE_ENTITY_H

#include "Date.h"

class BaseEntity {
protected:
    int id;
    Date createdAt;

    // Стандартен път за нови обекти.
    BaseEntity();

    // Път за възстановяване от файл със запазени id и дата.
    BaseEntity(int id, const Date& createdAt);

    static void ensureNextIdAtLeast(int usedId);

private:
    static int nextId;

public:
    int getId() const;
    Date getCreatedAt() const;

    virtual void displayInfo() const = 0;
    virtual ~BaseEntity();
};

#endif
