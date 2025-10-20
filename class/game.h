#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <array>
#include <cmath>
#include <memory>

#include "office.h"
#include "labtop.h"

class Game
{
public:
    Game()
    {
        office.changeVisible();
    }
    SDL_AppResult iterate()
    {
        if(_nightTime == 0) return SDL_APP_SUCCESS;
        //_nightTime--;

        if(_energy <= 0){ _rechargEnergy = 1; }
        else if( _energy >= 100){ _rechargEnergy = 0; }

        if(_rechargEnergy && labtop.itVisible())
        {
            office.changeVisible();
            labtop.changeVisible();
        }

        SDL_SetRenderViewport(renderer, &full_viewport);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        _energy += office.draw();
        _energy += labtop.draw();
        return SDL_APP_CONTINUE;
    }

    void changeEnergy(float energy)
    {
        _energy += energy;
    }
    void gameEvent(SDL_KeyboardEvent key)
    {
        if(key.key == SDLK_S && !office.getPosition() && !_rechargEnergy)
        {
            office.changeVisible();
            labtop.changeVisible();
        }
        else if(labtop.itVisible() && (key.key >= SDLK_0 && key.key <= SDLK_9))
        {
            labtop.switchCamera(key.key - SDLK_0);
        }
        else if(office.itVisible())
        {
            if(key.key == SDLK_A){ office.changeCameraPosition(0); }
            else if(key.key == SDLK_D){ office.changeCameraPosition(1); }
            else if(key.key == SDLK_S){ office.changeDoorStatus(); }
        }
    }
private:
    size_t _nightTime = 1000;

    float _energy = 100.0;
    bool _rechargEnergy = 0;

    bool _doorStatus = 0;
    bool _windowStatus = 0;

    OfficeScene office = OfficeScene
    {
        std::array<object, SIZE_OFFICE>
            {
                object {{0, 0, (float)width * 3, (float)height}, {0, 0, 255, 255}}, //Офисс
                object {{0, (float)height / 10, (float)width * 2 / 5, (float)height * 5 / 10}, {0, 255, 0, 255}},//Окно
                object {{(float)width * 13 / 5, (float)height / 10, (float)width * 2 / 5, (float)height * 9 / 10}, {0, 255, 0, 255}}//Дверь
            }
    };

    LabtopScene labtop = LabtopScene
    {
        std::array<SDL_Color, SIZE_LABTOP>
            {
                SDL_Color {218, 131, 225, 255},
                SDL_Color {70, 83, 15, 255},
                SDL_Color {177, 29, 22, 255},
                SDL_Color {126, 65, 101, 255},
                SDL_Color {2, 70, 189, 255},
                SDL_Color {67, 34, 116, 255},
                SDL_Color {180, 20, 3, 255},
                SDL_Color {27, 45, 80, 255},
                SDL_Color {187, 179, 230, 255},
                SDL_Color {203, 73, 176, 255}
            }
    };
};

Game game;