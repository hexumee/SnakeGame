#ifndef LTEXTURE_H
#define LTEXTURE_H

#include <fstream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

class Texture {
    public:
        Texture();
        bool loadFromFile(const std::string &path, SDL_Renderer* renderer);
        bool loadFromRenderedText(const std::string &textTexture, SDL_Color textColor, TTF_Font* mFont, SDL_Renderer* renderer);
        void freeTexture();
        void render(int x, int y, SDL_Renderer* renderer);
        int getWidth() const;
        int getHeight() const;
        ~Texture();
    private:
        SDL_Texture *texture;
        int width;
        int height;
};

#endif // LTEXTURE_H

