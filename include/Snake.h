#ifndef SNAKE_H
#define SNAKE_H

#include <deque>
#include "SDL.h"
#include "Object.h"

enum Direction {UP, RIGHT, DOWN, LEFT, NONE};

class Snake : public Object {
    public:
        bool hasCollided;
        Snake();
        void grow();
        void move();
        void setCollisionState(bool state);
        bool getCollisionState() const;
        bool checkForCollision() const;
        int getFrontX() const;
        int getFrontY() const;
        int getPosX(int pos) const;
        int getPosY(int pos) const;
        Direction getDirection() const;
        void setDirection(Direction value);
        unsigned long getLength() const;
        ~Snake();
    private:
        std::deque<SDL_Point> snakePos;
        SDL_Rect body{};
        Direction direction;
        void moveToDirection();
};

#endif // SNAKE_H

