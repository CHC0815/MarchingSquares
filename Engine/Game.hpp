#pragma once
#include <SDL.h>
#include <SDL_Image/include/SDL2/SDL_image.h>
#include <vector>
#include "InputManager.hpp"

class ColliderComponent;

class Game
{

public:
    Game();
    ~Game();

    void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);

    void handleEvents();
    void update();
    void render();
    void clean();

    bool running()
    {
        return isRunning;
    }

    static SDL_Renderer *renderer;
    static SDL_Event event;
    static std::vector<ColliderComponent *> colliders;

    static int mouse_x;
    static int mouse_y;
    static InputManager *inputManager;

    static float deltaTime;

private:
    int count = 0;
    bool isRunning;
    SDL_Window *window;
};
