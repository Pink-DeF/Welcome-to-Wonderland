#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <array>
#include <map>
#include <cmath>
#include "preset.h"

#define ENERGY_CAPACITY 3000.0

struct object
{
    void draw()
    {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &position);
    }

    SDL_FRect position = {0, 0 , 0, 0};
    SDL_Color color = {0, 0, 0, 0};
};

struct nightDB
{
    nightDB(size_t data): night(data){}

    //render info

    const int width = config.getWidth();
    const int height = config.getHeight();
    
    //game info
    const size_t night = 1;

    float energy = ENERGY_CAPACITY;
    bool rechargEnergy = 0;

    std::array<size_t, 4> enemyPosition;
    
    std::array<std::map<size_t, object>, 4> enemyFrame =
    {
        std::map<size_t, object>
        {
            {0, object {SDL_FRect {100, 100, 400, 400}}},
            {5, object {SDL_FRect {100, 100, 400, 400}}},
            {6, object {SDL_FRect {100, 100, 400, 400}}},
            {7, object {SDL_FRect {100, 100, 400, 400}}},
            {9, object {SDL_FRect {100, 100, 400, 400}}},
            {12, object {SDL_FRect {100, 100, 400, 400}}}
        }
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