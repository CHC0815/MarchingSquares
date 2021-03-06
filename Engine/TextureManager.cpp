#include "TextureManager.hpp"

SDL_Texture *TextureManager::LoadTexture(const char *fileName)
{
    SDL_Surface *tmpSurface = IMG_Load(fileName);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
    return tex;
}

void TextureManager::Draw(SDL_Texture *texture, SDL_Rect src, SDL_Rect dest)
{
    SDL_RenderCopy(Game::renderer, texture, &src, &dest);
}

void TextureManager::Draw(SDL_Texture *texture, SDL_Rect dest)
{
    SDL_RenderCopy(Game::renderer, texture, NULL, &dest);
}

void TextureManager::Draw(SDL_Texture *texture)
{
    SDL_RenderCopy(Game::renderer, texture, NULL, NULL);
}