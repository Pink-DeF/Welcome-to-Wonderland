#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <array>
#include <cmath>

#define SIZE_ENEMY 11

struct object
{
    SDL_FRect position;
    SDL_Color color;
};

class Scene
{
public:
    virtual float draw() = 0;
    void changeVisible(){ _visible = !_visible; }
    bool itVisible(){ return _visible; }

protected:
    bool _visible = false;
};

class Enemy
{
public:
    virtual size_t move() = 0;
private:
    std::array<bool, SIZE_ENEMY> _manyPosition;
    size_t _position;
    bool _active = 0;
};