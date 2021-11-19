#include "../include/Config.h"
#include "../include/Snake.h"

Snake::Snake() {
    pos.x = COL_SIZE/2;
    pos.y = ROW_SIZE/2;

    body.x = 0;
    body.y = 0;
    body.w = IMAGE_WIDTH;
    body.h = IMAGE_HEIGHT;

    snakePos.push_front(pos);

    direction = NONE;
    hasCollided = false;
}

Snake::~Snake() = default;

void Snake::grow() {
    moveToDirection();
    snakePos.push_front(pos);
}

void Snake::move() {
    for (unsigned long i = snakePos.size()-1; i > 0; --i) {
        snakePos[i].x = snakePos[i-1].x;
        snakePos[i].y = snakePos[i-1].y;
    }
    
    moveToDirection();
    snakePos.front() = pos;
}

void Snake::moveToDirection() {
    pos = snakePos.front();

    switch (direction) {
        case RIGHT:
            pos.x++;
            break;
        case LEFT:
            pos.x--;
            break;
        case UP:
            pos.y--;
            break;
        case DOWN:
            pos.y++;
            break;
        case NONE:
            break;
    }
}

bool Snake::getCollisionState() const {
    return hasCollided;
}

void Snake::setCollisionState(bool state) {
    hasCollided = state;
}

int Snake::getFrontX() const {
    return snakePos.front().x;
}

int Snake::getFrontY() const {
    return snakePos.front().y;
}

int Snake::getPosX(int pos) const {
    return snakePos[pos].x;
}

int Snake::getPosY(int pos) const {
    return snakePos[pos].y;
}

unsigned long Snake::getLength() const {
    return snakePos.size();
}

Direction Snake::getDirection() const {
    return direction;
}

void Snake::setDirection(Direction value) {
    direction = value;
}

bool Snake::checkForCollision() const {
    for (unsigned long i = 1; i < snakePos.size(); ++i) {
        if ((snakePos.front().x == snakePos[i].x) && (snakePos.front().y == snakePos[i].y)) {
            return true;
        }
    }
    return false;
}

