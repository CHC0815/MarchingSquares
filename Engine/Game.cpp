#include "Game.hpp"
#include "TextureManager.hpp"
#include "ECS/Components.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"

SDL_Renderer *Game::renderer = nullptr;
Manager manager;
SDL_Event Game::event;
std::vector<ColliderComponent *> Game::colliders;

Game::Game()
{
}

Game::~Game()
{
}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{

    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystems Initialized!..." << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window)
        {
            std::cout << "Window created!..." << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer created!..." << std::endl;
        }

        isRunning = true;
    }
    else
    {
        isRunning = false;
    }

    auto &entity = manager.createEntity();
    entity.addComponent<TransformComponent>();
    entity.addComponent<SpriteComponent>("assets/player.bmp", 230, 398);
    entity.getComponent<TransformComponent>().scale = Vector2D(1, 1);
}

void Game::handleEvents()
{
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    default:
        break;
    }
}
void Game::update()
{
    manager.update();
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 100, 149, 237, 255); // clear in cornflower blue
    SDL_RenderClear(renderer);

    manager.draw();

    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleaned!" << std::endl;
}
