#include "Game.hpp"

#include <iostream>

Game *game = nullptr;

static int WIDTH = 800;
static int HEIGHT = 640;

int main(int argc, char *argv[])
{
    const float FPS = 60;
    const float frameDelay = 1000.0000 / FPS;

    Uint32 frameStart;
    int frameTime;

    game = new Game();
    game->init("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, false);
    while (game->running())
    {
        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        //delay
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
        game->deltaTime = (float)((SDL_GetTicks() - frameStart) / 1000.0000);
    }

    game->clean();

    free(game);

    return 0;
}