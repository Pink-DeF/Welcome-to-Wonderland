#pragma once

struct Texture
{
    Texture(){}
    Texture(SDL_Texture* img, SDL_FRect pos, SDL_FRect siz): texture(img), position(pos), size(siz){}

    void draw() { SDL_RenderTexture(renderer, texture, &(size), &(position)); }
    SDL_Texture* texture = nullptr;
    SDL_FRect position = {0, 0, 0 ,0};
    SDL_FRect size = {0, 0, 0, 0};
};