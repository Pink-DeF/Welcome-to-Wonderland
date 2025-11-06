#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <array>
#include <cmath>

struct object
{
    SDL_FRect position;
    SDL_Color color;
};

struct nightDB
{
    nightDB(size_t data): night(data){}
    bool live = 1;

    const size_t night = 0;
    size_t nightTime = 10000;
    size_t monitorTime = 0;

    float energy = 100.0;
    bool rechargEnergy = 0;

    bool leftDoorStatus = 0;
    bool rightDoorStatus = 0;

    std::array<size_t, 4> enemyPosition;
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