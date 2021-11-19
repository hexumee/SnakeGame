#ifndef FOOD_H
#define FOOD_H

#include "Config.h"
#include "Map.h"
#include "Object.h"

class Food : public Object {
    public:
        Food();
        void setFood(Map& map);
        void setEatenState(bool state);
        ~Food();
    private:
        bool isEaten;
};

#endif // FOOD_H

