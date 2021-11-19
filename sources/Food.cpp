#include <ctime>
#include <vector>
#include "../include/Food.h"

Food::Food() {
    std::srand(time(nullptr));
    isEaten = false;
}

Food::~Food() = default;

void Food::setFood(Map &map) {
    std::vector<SDL_Point> availableSpace;
    SDL_Point point;
    int chosenSpace;

    if (isEaten) {
        for (int i = 0; i < ROW_SIZE; ++i) {
            for (int j = 0; j < COL_SIZE; ++j) {
                if (map.getSymbol(j, i) == EMPTY) {
                    point.x = j;
                    point.y = i;
                    availableSpace.push_back(point);
                }
            }
        }

        chosenSpace = std::rand() % availableSpace.size();
        pos.x = availableSpace[chosenSpace].x;
        pos.y = availableSpace[chosenSpace].y;
        isEaten = false;
    }
}

void Food::setEatenState(bool state) {
    isEaten = state;
}

