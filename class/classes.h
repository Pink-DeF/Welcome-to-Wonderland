#pragma once
#include <map>
#include "preset.h"

using namespace GameConstant;

struct Texture
{
    Texture(){}
    Texture(SDL_Texture* img, SDL_FRect pos, SDL_FRect siz): texture(img), position(pos), size(siz){}

    void draw() { SDL_RenderTexture(renderer, texture, &(size), &(position)); }
    SDL_Texture* texture = nullptr;
    SDL_FRect position = {0, 0, 0 ,0};
    SDL_FRect size = {0, 0, 0, 0};
};

struct object
{
    void draw()
    {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &position);
    }

    SDL_FRect position = {0, 0 , 0, 0};
    SDL_Color color = {0, 0, 0, 0};

    object operator+(object obj)
    {
        obj.position.x += position.x;
        obj.position.y += position.y;
        return obj;
    }
};

struct paralax
{
    float currentPositionX = 0.0f;
    float currentPositionY= 0.0f;

    float targetPositionX = 0.0f;
    float targetPositionY= 0.0f;
};

struct nightDB
{
    nightDB(){}
    
    //game info
    float energy = ENERGY_CAPACITY;
    bool rechargEnergy = 0;

    size_t invertTime = 0;

    std::array<size_t, 4> enemyPosition = {0, 0, 4, 3};
    size_t MasterFakePosition = 10;

    std::array<Texture, ENEMY_COUNT> enemyDoorTexture =
    {
        Texture{IMG_LoadTexture(renderer, "Texture/legenda.jpg"),
                SDL_FRect{static_cast<float>(config.getWidth()) * 13 / 5, static_cast<float>(config.getHeight()) * 1 / 10, static_cast<float>(config.getWidth()) * 2 / 5, static_cast<float>(config.getHeight()) * 9 / 10},
                SDL_FRect{180, 150, 350, 700}},
        Texture{IMG_LoadTexture(renderer, "Texture/doomguy.jpg"),
                SDL_FRect{0, static_cast<float>(config.getHeight()) / 10, static_cast<float>(config.getWidth()) * 2 / 5, static_cast<float>(config.getHeight()) * 5 / 10},
                SDL_FRect{800, 0, 1250, 2400}},
        Texture{IMG_LoadTexture(renderer, "Texture/Senko.png"),
                SDL_FRect{static_cast<float>(config.getWidth()) * 13 / 5, static_cast<float>(config.getHeight()) * 1 / 10, static_cast<float>(config.getWidth()) * 2 / 5, static_cast<float>(config.getHeight()) * 9 / 10},
                SDL_FRect{0, 0, 1447, 2039}},
        Texture{IMG_LoadTexture(renderer, "Texture/master.jpg"),
                SDL_FRect{0, static_cast<float>(config.getHeight()) / 10, static_cast<float>(config.getWidth()) * 2 / 5, static_cast<float>(config.getHeight()) * 5 / 10},
                SDL_FRect{40, 130, 1400, 1450}}
    };

    std::map<size_t, size_t> _distanceToOffice = {
        {0, 4}, {1, 4},
        {2, 3}, {3, 3,},
        {4, 2}, {5, 2},
        {6, 2}, {7, 3},
        {8, 2}, {9, 2},
        {10, 0}, {11, 0}
    };
};

class Scene
{
public:
    virtual void draw() = 0;
    void changeVisible(){ _visible = !_visible; }
    bool itVisible(){ return _visible; }

protected:
    bool _visible = false;
};