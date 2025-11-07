#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <array>
#include <cmath>

#define ENERGY_CAPACITY 5000000.0

struct object
{
    SDL_FRect position = {0, 0 , 0, 0};
    SDL_Color color = {0, 0, 0, 0};
};

struct nightDB
{
    nightDB(size_t data): night(data){}
    bool live = 1;

    const size_t night = 0;
    size_t nightTime = 10000;
    size_t monitorTime = 0;

    float energy = ENERGY_CAPACITY;
    bool rechargEnergy = 0;

    bool leftDoorStatus = 0;
    bool rightDoorStatus = 0;

    std::array<size_t, 4> enemyPosition;
    const std::array<std::array<object, 12>, 4> enemyFrame =
    {
        std::array<object, 12> {
            object {SDL_FRect {100, 100, 400, 400}, SDL_Color {0, 0, 0 ,255}},object {SDL_FRect {100, 100, 400, 400}, SDL_Color {0, 0, 0 ,255}},
            object {SDL_FRect {100, 100, 400, 400}, SDL_Color {0, 0, 0 ,255}},object {SDL_FRect {100, 100, 400, 400}, SDL_Color {0, 0, 0 ,255}},
            object {SDL_FRect {100, 100, 400, 400}, SDL_Color {0, 0, 0 ,255}},object {SDL_FRect {100, 100, 400, 400}, SDL_Color {0, 0, 0 ,255}},
            object {SDL_FRect {100, 100, 400, 400}, SDL_Color {0, 0, 0 ,255}},object {SDL_FRect {100, 100, 400, 400}, SDL_Color {0, 0, 0 ,255}},
            object {SDL_FRect {100, 100, 400, 400}, SDL_Color {0, 0, 0 ,255}},object {SDL_FRect {100, 100, 400, 400}, SDL_Color {0, 0, 0 ,255}},
        },
        std::array<object, 12> {
            object {SDL_FRect {100, 100, 400, 400}, SDL_Color {0, 0, 0 ,255}},object {SDL_FRect {100, 100, 400, 400}, SDL_Color {0, 0, 0 ,255}},
            object {SDL_FRect {100, 100, 400, 400}, SDL_Color {0, 0, 0 ,255}},object {SDL_FRect {100, 100, 400, 400}, SDL_Color {0, 0, 0 ,255}},
            object {SDL_FRect {100, 100, 400, 400}, SDL_Color {0, 0, 0 ,255}},object {SDL_FRect {100, 100, 400, 400}, SDL_Color {0, 0, 0 ,255}},
            object {SDL_FRect {100, 100, 400, 400}, SDL_Color {0, 0, 0 ,255}},object {SDL_FRect {100, 100, 400, 400}, SDL_Color {0, 0, 0 ,255}},
            object {SDL_FRect {100, 100, 400, 400}, SDL_Color {0, 0, 0 ,255}},object {SDL_FRect {100, 100, 400, 400}, SDL_Color {0, 0, 0 ,255}},
        },
        std::array<object, 12> {
            object {SDL_FRect {100, 100, 400, 400}, SDL_Color {0, 0, 0 ,255}},object {SDL_FRect {100, 100, 400, 400}, SDL_Color {0, 0, 0 ,255}},
            object {SDL_FRect {100, 100, 400, 400}, SDL_Color {0, 0, 0 ,255}},object {SDL_FRect {100, 100, 400, 400}, SDL_Color {0, 0, 0 ,255}},
            object {SDL_FRect {100, 100, 400, 400}, SDL_Color {0, 0, 0 ,255}},object {SDL_FRect {100, 100, 400, 400}, SDL_Color {0, 0, 0 ,255}},
            object {SDL_FRect {100, 100, 400, 400}, SDL_Color {0, 0, 0 ,255}},object {SDL_FRect {100, 100, 400, 400}, SDL_Color {0, 0, 0 ,255}},
            object {SDL_FRect {100, 100, 400, 400}, SDL_Color {0, 0, 0 ,255}},object {SDL_FRect {100, 100, 400, 400}, SDL_Color {0, 0, 0 ,255}},
        },
        std::array<object, 12> {
            object {SDL_FRect {100, 100, 400, 400}, SDL_Color {0, 0, 0 ,255}},object {SDL_FRect {100, 100, 400, 400}, SDL_Color {0, 0, 0 ,255}},
            object {SDL_FRect {100, 100, 400, 400}, SDL_Color {0, 0, 0 ,255}},object {SDL_FRect {100, 100, 400, 400}, SDL_Color {0, 0, 0 ,255}},
            object {SDL_FRect {100, 100, 400, 400}, SDL_Color {0, 0, 0 ,255}},object {SDL_FRect {100, 100, 400, 400}, SDL_Color {0, 0, 0 ,255}},
            object {SDL_FRect {100, 100, 400, 400}, SDL_Color {0, 0, 0 ,255}},object {SDL_FRect {100, 100, 400, 400}, SDL_Color {0, 0, 0 ,255}},
            object {SDL_FRect {100, 100, 400, 400}, SDL_Color {0, 0, 0 ,255}},object {SDL_FRect {100, 100, 400, 400}, SDL_Color {0, 0, 0 ,255}},
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