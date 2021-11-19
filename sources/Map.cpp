#include "../include/Map.h"

Map::Map() {
    clearMap();
}

Map::~Map() = default;

void Map::clearMap() {
    for (int i = 0; i < ROW_SIZE; ++i) {
        for (int j = 0; j < COL_SIZE; ++j) {
            pos[i][j] = EMPTY;
        }
    }
}

char Map::getSymbol(int x, int y) const {
    return pos[y][x];
}

void Map::setSymbol(int x, int y, char symbol) {
    pos[y][x] = symbol;
}

