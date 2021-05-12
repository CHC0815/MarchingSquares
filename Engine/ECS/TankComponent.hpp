#pragma once

#include "Components.hpp"
#include "SDL.h"
#include "../TextureManager.hpp"
#include "../util.hpp"
#include "../InputManager.hpp"
#include <cmath>

class TankComponent : public Component
{
private:
    SDL_Texture *bottom;
    SDL_Texture *top;

    SDL_Point centerTop;
    SDL_Point centerBottom;

    SDL_Rect destBottom;
    SDL_Rect destTop;

    float topAngle = 0.0;
    float bottomAngle = 0.0;

    float rotationSpeed = 45.0;
    float moveSpeed = 20.0;

public:
    void init() override
    {
        if (!entity->hasComponent<TransformComponent>())
        {
            entity->addComponent<TransformComponent>(100, 100);
        }
        bottom = TextureManager::LoadTexture("assets/tank.png");
        top = TextureManager::LoadTexture("assets/turret.png");

        centerTop.x = 30;
        centerTop.y = 92;
        centerBottom.x = 76;
        centerBottom.y = 79;

        destBottom.w = 154;
        destBottom.h = 160;
        destTop.w = 59;
        destTop.h = 116;
    }

    Vector2D moveBy = Vector2D(0, 0);
    void update() override
    {
        //bottom
        destBottom.x = static_cast<int>(entity->getComponent<TransformComponent>().position.x);
        destBottom.y = static_cast<int>(entity->getComponent<TransformComponent>().position.y);
        //top
        destTop.x = destBottom.x + centerBottom.x - centerTop.x;
        destTop.y = destBottom.y + centerBottom.y - centerTop.y;

        //rotate top section
        topAngle = util::getAngle(Game::mouse_x, Game::mouse_y, destTop.x + centerTop.x, destTop.y + centerTop.y) + 180;

        //rotate bottom section
        if (InputManager::Instance()->KeyDown(SDL_SCANCODE_D))
        {
            bottomAngle += rotationSpeed * Game::deltaTime;
        }
        if (InputManager::Instance()->KeyDown(SDL_SCANCODE_A))
        {
            bottomAngle -= rotationSpeed * Game::deltaTime;
        }
        //move bottom section
        moveBy.x = cos(bottomAngle) * moveSpeed * Game::deltaTime;
        moveBy.y = sin(bottomAngle) * moveSpeed * Game::deltaTime;
        entity->getComponent<TransformComponent>().position += moveBy;
    }
    void draw() override
    {
        SDL_RenderCopyEx(Game::renderer, bottom, NULL, &destBottom, bottomAngle, &centerBottom, SDL_FLIP_NONE);
        SDL_RenderCopyEx(Game::renderer, top, NULL, &destTop, topAngle, &centerTop, SDL_FLIP_NONE);
        Vector2D pos = entity->getComponent<TransformComponent>().position;
        SDL_RenderDrawLine(Game::renderer, (int)pos.x, (int)pos.y, (int)pos.x + moveBy.x, (int)pos.y + moveBy.y);
    }
};
