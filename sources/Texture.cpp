#include "../include/Texture.h"

Texture::Texture() {
    texture = nullptr;
    width = 0;
    height = 0;
}

Texture::~Texture() {
    freeTexture();
}

bool Texture::loadFromFile(const std::string &path, SDL_Renderer* renderer) {
    freeTexture();
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    width = loadedSurface->w;
    height = loadedSurface->h;
    SDL_FreeSurface(loadedSurface);
    texture = newTexture;

    return texture != nullptr;
}

bool Texture::loadFromRenderedText(const std::string &textTexture, SDL_Color textColor, TTF_Font* mFont, SDL_Renderer* renderer) {
    freeTexture();
    SDL_Surface* textSurface = TTF_RenderText_Solid(mFont, textTexture.c_str(), textColor);
    texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    width = textSurface->w;
    height = textSurface->h;
    SDL_FreeSurface(textSurface);

    return texture != nullptr;
}

void Texture::freeTexture() {
    if (texture == nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
        width = 0;
        height = 0;
    }
}

void Texture::render(int x, int y, SDL_Renderer *renderer) {
    SDL_Rect renderQuad = {x, y, width, height};
    SDL_RenderCopy(renderer, texture, nullptr, &renderQuad);
}

int Texture::getWidth() const {
    return width;
}

int Texture::getHeight() const {
    return height;
}

