#ifndef OBJECT_H
#define OBJECT_H

#include "SDL.h"
#include "Texture.h"

class Object {
    public:
        Object();
        int getPosX() const;
        int getPosY() const;
        Texture texture;
        ~Object();
    protected:
        SDL_Point pos{};
};

#endif // OBJECT_H

