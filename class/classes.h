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
    
    std::array<std::map<size_t, object>, ENEMY_COUNT> enemyFrame =
    {
        std::map<size_t, object>
        {
            {0, object {SDL_FRect {50, 100, 400, 400}, SDL_Color {50, 100, 60, 255}}},
            {5, object {SDL_FRect {50, 100, 400, 400}, SDL_Color {50, 100, 60, 255}}},
            {6, object {SDL_FRect {50, 100, 400, 400}, SDL_Color {50, 100, 60, 255}}},
            {7, object {SDL_FRect {50, 100, 400, 400}, SDL_Color {50, 100, 60, 255}}},
            {9, object {SDL_FRect {50, 100, 400, 400}, SDL_Color {50, 100, 60, 255}}},
            {10, object {SDL_FRect {30, 50, 300, 600}, SDL_Color{100, 200, 100, 255}}}
        },
        std::map<size_t, object>
        {
            {0, object {SDL_FRect {600, 200, 300, 300}, SDL_Color {150, 150, 0, 255}}},
            {4, object {SDL_FRect {600, 200, 300, 300}, SDL_Color {150, 150, 0, 255}}},
            {5, object {SDL_FRect {600, 200, 300, 300}, SDL_Color {150, 150, 0, 255}}},
            {7, object {SDL_FRect {600, 200, 300, 300}, SDL_Color {150, 150, 0, 255}}},
            {9, object {SDL_FRect {600, 200, 300, 300}, SDL_Color {150, 150, 0, 255}}},
            {11, object {SDL_FRect {30, 50, 300, 300}, SDL_Color{150, 150, 0, 255}}}
        },
        std::map<size_t, object>
        {
            {3, object {SDL_FRect {500, 100, 300, 300}, SDL_Color {100, 100, 100, 100}}},
            {4, object {SDL_FRect {500, 100, 300, 300}, SDL_Color {100, 100, 100, 100}}},
            {8, object {SDL_FRect {500, 100, 300, 300}, SDL_Color {100, 100, 100, 100}}},
            {9, object {SDL_FRect {500, 100, 300, 300}, SDL_Color {100, 100, 100, 100}}},
            {11, object {SDL_FRect {30, 50, 300, 600}, SDL_Color {100, 100, 100, 100}}},
        },
        std::map<size_t, object>
        {
            {3, object {SDL_FRect {100, 400, 300, 350}, SDL_Color {255, 0, 100, 255}}},
            {5, object {SDL_FRect {100, 400, 300, 350}, SDL_Color {255, 0, 100, 255}}},
            {7, object {SDL_FRect {100, 400, 300, 350}, SDL_Color {255, 0, 100, 255}}},
            {8, object {SDL_FRect {100, 400, 300, 350}, SDL_Color {255, 0, 100, 255}}},
            {10, object {SDL_FRect {30, 50, 400, 300}, SDL_Color {255, 0, 100, 255}}},
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