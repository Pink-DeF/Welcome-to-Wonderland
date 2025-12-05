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