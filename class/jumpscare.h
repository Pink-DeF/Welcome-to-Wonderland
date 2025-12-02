#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <array>
#include <map>
#include <cmath>
#include "classes.h"

class JumpscareScene: public Scene
{
public:
    JumpscareScene(size_t ID) { _enemyID = ID; changeVisible(); }
    
    void draw() override
    {
        if(timer == 0){ return; }
        SDL_SetRenderViewport(renderer, NULL);
        SDL_SetRenderDrawColor(renderer, _frames[_enemyID].r, _frames[_enemyID].g, _frames[_enemyID].b, 255);
        SDL_RenderFillRect(renderer, &rend);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

        timer--;
        SDL_Delay(15);
        draw();
    }

private:
    size_t _enemyID = 10;
    size_t timer = 100;

    SDL_FRect rend {0, 0, static_cast<float>(config.getWidth()), static_cast<float>(config.getHeight())};

    std::map<size_t, SDL_Color> _frames
    {
        {SPRINGTIME_ID, SDL_Color {100, 200, 100, 255}},
        {ERRORTIME_ID,  SDL_Color {150, 150, 0, 255}},
        {MASTEROFPUPPET_ID, SDL_Color {100, 100, 100, 255}},
        {FOXDEN_ID, SDL_Color {255, 0, 100, 255}}
    };
};