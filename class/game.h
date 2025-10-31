#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <array>
#include <cmath>
#include <memory>

#include "office.h"
#include "labtop.h"
#include "enemy.h"

#define ENEMY_COUNT 4

class Night
{
public:
    Night(size_t night) : _night(night), _springTime(night)
    {
        office.changeVisible();
    }
    SDL_AppResult iterate()
    {
        if(_nightTime == 0) return SDL_APP_SUCCESS;
        //_nightTime--;

        if(_energy <= 0){ _rechargEnergy = 1; }
        else if( _energy >= 100){ _rechargEnergy = 0; }

        if(_rechargEnergy)
        {
            if(labtop.itVisible())
            {
                office.changeVisible();
                labtop.changeVisible();
            }
            
            office.openAll();
        }

        SDL_SetRenderViewport(renderer, NULL);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        _energy += office.draw();
        _energy += labtop.draw();
        _monitorTime += labtop.itVisible();
        return SDL_APP_CONTINUE;
    }

    void changeEnergy(float energy)
    {
        _energy += energy;
    }
    void gameEvent(SDL_KeyboardEvent key)
    {
        if(key.key == SDLK_S && !office.getCameraPosition() && !_rechargEnergy)
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
            else if(!_rechargEnergy && key.key == SDLK_S){ office.changeDoorStatus(); }
        }
    }
private:
    const size_t _night = 0; //Номер ночи, для коррекции поведения противников
    size_t _nightTime = 1000; //Время отведенное на ночь
    size_t _monitorTime = 0; // Счетчик времени в мониторе, нужен для коррекции поведения противников

    float _energy = 100.0; //Максимальная энергия, для планшета и дверей
    bool _rechargEnergy = 0; //Статус перезарядки энергии, нужен для отката методов зависящих от энергии

    bool _doorStatus = 0; //Статус закрытия правой двери
    bool _windowStatus = 0; //Статус закрытия левого окна

    std::array<size_t, ENEMY_COUNT> _enemy; //Массив противников

    SpringTime _springTime = (0);

    OfficeScene office = OfficeScene //Сцена Офиса и его компонентов
    {
        std::array<object, SIZE_OFFICE>
            {
                object {{0, 0, (float)width * 3, (float)height}, {0, 0, 255, 255}}, //Офисс
                object {{0, (float)height / 10, (float)width * 2 / 5, (float)height * 5 / 10}, {0, 255, 0, 255}},//Окно
                object {{(float)width * 13 / 5, (float)height / 10, (float)width * 2 / 5, (float)height * 9 / 10}, {0, 255, 0, 255}}//Дверь
            }
    };

    LabtopScene labtop = LabtopScene //Сцена планшета и камер
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