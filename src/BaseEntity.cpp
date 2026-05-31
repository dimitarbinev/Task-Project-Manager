#include "BaseEntity.h"

#include <stdexcept>

int BaseEntity::nextId = 1;

BaseEntity::BaseEntity() : id(nextId++), createdAt(Date::today()) {
}

BaseEntity::BaseEntity(int id, const Date& createdAt) : id(id), createdAt(createdAt) {
    if (id < 1) {
        throw std::invalid_argument("Entity ID must be positive.");
    }

    ensureNextIdAtLeast(id);
}

void BaseEntity::ensureNextIdAtLeast(int usedId) {
    if (usedId >= nextId) {
        nextId = usedId + 1;
    }
}

int BaseEntity::getId() const {
    return id;
}

Date BaseEntity::getCreatedAt() const {
    return createdAt;
}

BaseEntity::~BaseEntity() {
}
