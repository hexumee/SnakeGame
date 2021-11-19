#include "../include/Object.h"

Object::Object() {
    pos.x = 0;
    pos.y = 0;
}

Object::~Object() = default;

int Object::getPosX() const {
    return pos.x;
}

int Object::getPosY() const {
    return pos.y;
}

