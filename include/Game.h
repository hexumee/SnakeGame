#ifndef GAME_H
#define GAME_H

#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "Food.h"
#include "Texture.h"
#include "Map.h"
#include "Snake.h"

class Game {
    public:
        Game();
        void start();
        void createObjects();
        void eventListener();
        void updateObjects();
        void renderObjects();
        ~Game();
    private:
        bool isKeyPressed;
        bool isExitClicked;
        std::string score;
        SDL_Window* window;
        SDL_Surface *appIcon;
        SDL_Renderer* renderer;
        SDL_Event event{};
        TTF_Font* font{};
        Mix_Chunk *eatenApple;
        Mix_Chunk *gameOver;
        SDL_Color textColor{};
        Texture wall;
        Texture textScore;
        Texture textGameOver;
        Texture textActions;
        Texture scoreCounter;
        Snake snake;
        Snake snakeHeadLooksUp;
        Snake snakeHeadLooksDown;
        Snake snakeHeadLooksLeft;
        Snake snakeHeadLooksRight;
        Map map;
        Food food;
};

#endif // GAME_H

