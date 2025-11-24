#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <array>
#include <cmath>
#include <memory>

#include "office.h"
#include "labtop.h"
#include "enemy.h"

using namespace GameConstant;
class Night : public Scene
{
private:
    void setRechargEnergy()
    {
        if(_data->energy <= 0){ _data->rechargEnergy = 1; }
        else if(_data->energy >= ENERGY_CAPACITY){ _data->rechargEnergy = 0; }

        if(_data->rechargEnergy)
        {
            if(labtop.itVisible())
            {
                office.changeVisible();
                labtop.changeVisible();
            }
            
            office.changeDoorStatus(0);
        }
    }
    void draw() override
    {
        //SDL_SetRenderViewport(renderer, NULL);
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderClear(renderer);

        office.draw();
        labtop.draw();
        _monitorTime += labtop.itVisible();
    }

    void enemyMove()
    {
        _live = _springTime.attack(office.getLeftDoorStatus());
        _data->enemyPosition[0] = _springTime.move(_data->enemyPosition[0]);
    }

public:
    Night(size_t night): _data(std::make_shared<nightDB>(night))
    {
        office = OfficeScene //Сцена Офиса и его компонентов
        {
            std::array<object, SIZE_OFFICE>
                {
                    object {{-static_cast<float>(config.getWidth()), -(float)_data->height * 0.5f, static_cast<float>(config.getWidth())* 4, (float)_data->height * 2}, {0, 0, 255, 255}}, //Офисс
                    object {{0, (float)_data->height / 10, static_cast<float>(config.getWidth()) * 2 / 5, (float)_data->height * 5 / 10}, {0, 255, 0, 255}},//Окно
                    object {{static_cast<float>(config.getWidth()) * 13 / 5, (float)_data->height / 10, static_cast<float>(config.getWidth()) * 2 / 5, (float)_data->height * 9 / 10}, {0, 255, 0, 255}}//Дверь
                }, _data
        };

        labtop = LabtopScene //Сцена планшета и камер
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
                }, _data
        };

        office.changeVisible();
    }
    SDL_AppResult iterate()
    {
        if(_nightTime == 0 || _live == 0) return SDL_APP_SUCCESS;
        //_data.nightTime--;

        setRechargEnergy();
        enemyMove();

        draw();
        return SDL_APP_CONTINUE;
    }

    void gameEvent(SDL_KeyboardEvent& key)
    {
        if(key.key == SDLK_S && !office.getCameraPosition() && !_data->rechargEnergy)
        {
            office.changeVisible();
            labtop.changeVisible();
        }
        else if(labtop.itVisible() && (key.key >= SDLK_0 && key.key <= SDLK_9))
        {
            labtop.switchCamera(key.key - SDLK_0);
            if(labtop.itVisible()){ labtop.useShock(); }
        }
        else if(office.itVisible())
        {
            if(key.key == SDLK_A){ office.changeCameraPosition(0); }
            else if(key.key == SDLK_D){ office.changeCameraPosition(1); }
            else if(!_data->rechargEnergy && key.key == SDLK_S){ office.changeDoorStatus(1); }
            else if(!_data->rechargEnergy && key.key == SDLK_F){ office.changeDoorStatus(2); }
        }
    }
    void mouseEvent(SDL_MouseMotionEvent& motion)
    {
        if(office.itVisible())
        {
            office.mouseMotion(motion);
        }
    }

private:
    bool _live = 1;
    size_t _nightTime = BASED_NIGHT_TIME;
    size_t _monitorTime = 0;
    std::shared_ptr<nightDB> _data;

    SpringTime _springTime {_data};

    OfficeScene office; 
    LabtopScene labtop;
};