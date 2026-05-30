#include "../include/BaseEntity.h"

int BaseEntity::nextId = 1;

BaseEntity::BaseEntity() : id(nextId++), createdAt(Date::today()) {
}

int BaseEntity::getId() const {
    return id;
}

Date BaseEntity::getCreatedAt() const {
    return createdAt;
}

BaseEntity::~BaseEntity() {
}