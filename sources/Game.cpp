#include "../include/Game.h"
#include "../include/Config.h"
#include "../include/Snake.h"
#include "../include/Object.h"

Game::Game() {
    isKeyPressed = false;
    isExitClicked = false;
    score = "";
    textColor.r = 255;
    textColor.g = 255;
    textColor.b = 255;
    textColor.a = 255;

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    appIcon = IMG_Load("assets/icon.png");
    SDL_SetWindowIcon(window, appIcon);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    eatenApple = Mix_LoadWAV("assets/eatenApple.wav");
    gameOver = Mix_LoadWAV("assets/gameOver.wav");
}

Game::~Game() {
    TTF_CloseFont(font);
    TTF_Quit();
    IMG_Quit();
    Mix_FreeChunk(eatenApple);
    Mix_FreeChunk(gameOver);
    Mix_CloseAudio();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::start() {
    createObjects();

    while (!isExitClicked) {
        eventListener();
        if (!isExitClicked) {
            updateObjects();
            renderObjects();
        }
    }
}

void Game::createObjects() {
    font = TTF_OpenFont("assets/font.ttf", 25);
    food.texture.loadFromFile("assets/apple.png", renderer);
    snake.texture.loadFromFile("assets/snakeBody.png", renderer);
    snakeHeadLooksUp.texture.loadFromFile("assets/snakeHeadLooksUp.png", renderer);
    snakeHeadLooksDown.texture.loadFromFile("assets/snakeHeadLooksDown.png", renderer);
    snakeHeadLooksLeft.texture.loadFromFile("assets/snakeHeadLooksLeft.png", renderer);
    snakeHeadLooksRight.texture.loadFromFile("assets/snakeHeadLooksRight.png", renderer);
    wall.loadFromFile("assets/block.png", renderer);
    textScore.loadFromRenderedText("Score: ", textColor, font, renderer);
    textGameOver.loadFromRenderedText("Game over", textColor, font, renderer);
    textActions.loadFromRenderedText("Press esc to exit/enter to start new game", textColor, font, renderer);
    scoreCounter.loadFromRenderedText("0", textColor, font, renderer);
}

void Game::eventListener() {
    isKeyPressed = false;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            exit(0);
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                case SDLK_a:
                    if (snake.getDirection() != RIGHT && !snake.hasCollided) {
                        if (!isKeyPressed) {
                            snake.setDirection(LEFT);
                            isKeyPressed = true;
                        }
                    }
                    break;
                case SDLK_RIGHT:
                case SDLK_d:
                    if (snake.getDirection() != LEFT && !snake.hasCollided) {
                        if (!isKeyPressed) {
                            snake.setDirection(RIGHT);
                            isKeyPressed = true;
                        }
                    }
                    break;
                case SDLK_UP:
                case SDLK_w:
                    if (snake.getDirection() != DOWN && !snake.hasCollided) {
                        if (!isKeyPressed) {
                            snake.setDirection(UP);
                            isKeyPressed = true;
                        }
                    }
                    break;
                case SDLK_DOWN:
                case SDLK_s:
                    if (snake.getDirection() != UP && !snake.hasCollided) {
                        if (!isKeyPressed) {
                            snake.setDirection(DOWN);
                            isKeyPressed = true;
                        }
                    }
                    break;
                case SDLK_ESCAPE:
                    exit(0);
                case SDLK_RETURN:
                    SDL_DestroyRenderer(renderer);
                    SDL_DestroyWindow(window);
                    Game game;
                    game.start();
                    break;
            }
        }
    }
}

void Game::updateObjects() {
    if (!snake.getCollisionState()) {
        if (snake.getDirection() == RIGHT) {
            if (snake.getFrontX()+1 == COL_SIZE) {
                snake.setCollisionState(true);
                Mix_PlayChannel(-1, gameOver, 0);
            } else if (snake.checkForCollision()) {
                snake.setCollisionState(true);
                Mix_PlayChannel(-1, gameOver, 0);
            } else if ((snake.getFrontX()+1 == food.getPosX()) && (snake.getFrontY() == food.getPosY())) {
                Mix_PlayChannel(-1, eatenApple, 0);
                food.setEatenState(true);
                snake.grow();
            } else {
                snake.move();
            }
        } else if (snake.getDirection() == LEFT) {
            if (snake.getFrontX()-1 == -1) {
                snake.setCollisionState(true);
                Mix_PlayChannel(-1, gameOver, 0);
            } else if (snake.checkForCollision()) {
                snake.setCollisionState(true);
                Mix_PlayChannel(-1, gameOver, 0);
            } else if ((snake.getFrontX()-1 == food.getPosX()) && (snake.getFrontY() == food.getPosY())) {
                Mix_PlayChannel(-1, eatenApple, 0);
                food.setEatenState(true);
                snake.grow();
            }
            else {
                snake.move();
            }
        } else if (snake.getDirection() == UP) {
            if (snake.getFrontY()-1 == -1) {
                snake.setCollisionState(true);
                Mix_PlayChannel(-1, gameOver, 0);
            } else if (snake.checkForCollision()) {
                snake.setCollisionState(true);
                Mix_PlayChannel(-1, gameOver, 0);
            } else if ((snake.getFrontY()-1 == food.getPosY()) && (snake.getFrontX() == food.getPosX())) {
                Mix_PlayChannel(-1, eatenApple, 0);
                food.setEatenState(true);
                snake.grow();
            } else {
                snake.move();
            }
        } else if (snake.getDirection() == DOWN) {
            if (snake.getFrontY()+1 == ROW_SIZE) {
                snake.setCollisionState(true);
                Mix_PlayChannel(-1, gameOver, 0);
            } else if (snake.checkForCollision()) {
                snake.setCollisionState(true);
                Mix_PlayChannel(-1, gameOver, 0);
            } else if ((snake.getFrontY()+1 == food.getPosY()) && (snake.getFrontX() == food.getPosX())) {
                Mix_PlayChannel(-1, eatenApple, 0);
                food.setEatenState(true);
                snake.grow();
            } else {
                snake.move();
            }
        }
    }

    score = std::to_string(snake.getLength()-1);

    for (int i = 0; i < snake.getLength(); ++i) {
        map.setSymbol(snake.getPosX(i), snake.getPosY(i), SNAKE_SYMBOL);
    }

    food.setFood(map);
    map.setSymbol(food.getPosX(), food.getPosY(), FOOD_SYMBOL);
    map.clearMap();
}

void Game::renderObjects() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (int j = 0; j < COL_SIZE+2; ++j) {
        wall.render(j*wall.getWidth(), 0, renderer);
    }

    for (int i = 0; i < ROW_SIZE; ++i) {
        wall.render(0, i*wall.getHeight()+IMAGE_HEIGHT, renderer);
        wall.render(COL_SIZE*wall.getWidth()+IMAGE_WIDTH, i*wall.getHeight()+IMAGE_HEIGHT, renderer);
    }

    for (int j = 0; j < COL_SIZE+2; ++j) {
        wall.render(j*wall.getWidth(), ROW_SIZE*wall.getHeight()+IMAGE_HEIGHT, renderer);
    }

    food.texture.render(food.getPosX()*food.texture.getWidth()+IMAGE_WIDTH, food.getPosY()*food.texture.getHeight()+IMAGE_HEIGHT, renderer);

    for (int i = 0; i < snake.getLength(); ++i) {
        snake.texture.render(snake.getPosX(i)*snake.texture.getWidth()+IMAGE_WIDTH, snake.getPosY(i)*snake.texture.getHeight()+IMAGE_HEIGHT, renderer);

        if (snake.getDirection() == UP or snake.getDirection() == NONE) {
            snakeHeadLooksUp.texture.render(snake.getFrontX()*snakeHeadLooksUp.texture.getWidth()+IMAGE_WIDTH, snake.getFrontY()*snakeHeadLooksUp.texture.getHeight()+IMAGE_HEIGHT, renderer);
        } else if (snake.getDirection() == DOWN or snake.getDirection() == NONE) {
            snakeHeadLooksDown.texture.render(snake.getFrontX()*snakeHeadLooksDown.texture.getWidth()+IMAGE_WIDTH, snake.getFrontY()*snakeHeadLooksDown.texture.getHeight()+IMAGE_HEIGHT, renderer);
        } else if (snake.getDirection() == LEFT or snake.getDirection() == NONE) {
            snakeHeadLooksLeft.texture.render(snake.getFrontX()*snakeHeadLooksLeft.texture.getWidth()+IMAGE_WIDTH, snake.getFrontY()*snakeHeadLooksLeft.texture.getHeight()+IMAGE_HEIGHT, renderer);
        } else if (snake.getDirection() == RIGHT or snake.getDirection() == NONE) {
            snakeHeadLooksRight.texture.render(snake.getFrontX()*snakeHeadLooksRight.texture.getWidth()+IMAGE_WIDTH, snake.getFrontY()*snakeHeadLooksRight.texture.getHeight()+IMAGE_HEIGHT, renderer);
        } else {
            snake.texture.render(snake.getPosX(i)*snake.texture.getWidth()+IMAGE_WIDTH, snake.getPosY(i)*snake.texture.getHeight()+IMAGE_HEIGHT, renderer);
        }
    }

    textScore.render(10, 665, renderer);
    scoreCounter.loadFromRenderedText(score, textColor, font, renderer);
    scoreCounter.render(100, 665, renderer);

    if (snake.getCollisionState()) {
        textGameOver.render(270, 665, renderer);
        textActions.render(10, 715, renderer);
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(DELAY);
}

