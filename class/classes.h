#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <array>
#include <map>
#include <cmath>
#include "preset.h"

using namespace GameConstant;
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

    std::array<size_t, 4> enemyPosition = {0, 0, 0, 0};
    std::map<size_t, size_t> _distanceToOffice = {
        {0, 3}, {4, 2},
        {5, 1}, {6, 2},
        {7, 3}, {9, 1},
        {10, 0}
    };
    
    std::array<std::map<size_t, object>, ENEMY_COUNT> enemyFrame =
    {
        std::map<size_t, object>
        {
            {0, object {SDL_FRect {100, 100, 400, 400}}},
            {4, object {SDL_FRect {100, 100, 400, 400}}},
            {5, object {SDL_FRect {100, 100, 400, 400}}},
            {6, object {SDL_FRect {100, 100, 400, 400}}},
            {7, object {SDL_FRect {100, 100, 400, 400}}},
            {9, object {SDL_FRect {100, 100, 400, 400}}},
            {10, object {SDL_FRect {30, 50, 300, 600}, SDL_Color{100, 100, 100, 255}}}
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