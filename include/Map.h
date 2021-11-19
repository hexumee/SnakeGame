#ifndef MAP_H
#define MAP_H

#include "Config.h"

class Map {
    public:
        Map();
        void clearMap();
        void setSymbol(int x, int y, char symbol);
        char getSymbol(int x, int y) const;
        ~Map();
    private:
        char pos[ROW_SIZE][COL_SIZE]{};
};

#endif // MAP_H

