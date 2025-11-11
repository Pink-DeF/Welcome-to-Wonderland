#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <array>
#include <cmath>
#include "preset.h"

class MainMenuScene : public Scene
{
private:
    void draw() override
    {
        SDL_SetRenderViewport(renderer, NULL);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
    }

public:
    void iterate()
    {
    }

private:
    std::array<object, 3> _buttoms;
};