#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <array>
#include <cmath>
#include "preset.h"

#define SIZE_LABTOP 10

class LabtopScene: public Scene
{
private:
    class CameraScene : public Scene
    {
    public:
        //Конструктор
        CameraScene(){}
        CameraScene(SDL_Color tmp){ _object = object { SDL_FRect { 0, 0, (float)width, (float)height }, tmp}; } 
 
        void move(bool direct)
        {
            if(direct && width <= width / 2){ _viewport.x += width * 0.05; }
            else if(!direct && width >= 0){ _viewport.x -= width * 0.05; }
        }

        //Ппросто отрисовка
        void draw() override
        { 
            SDL_SetRenderViewport(renderer, &_viewport);
            SDL_SetRenderDrawColor(renderer, _object.color.r, _object.color.g, _object.color.b, _object.color.a);
            SDL_RenderFillRect(renderer, &(_object.position));
            return;
        }

    private:
        SDL_Rect _viewport = {0, 0, 2 * width, height};
        object _object;
    };

public:
    LabtopScene(std::array<SDL_Color, SIZE_LABTOP> tmp, std::shared_ptr<nightDB> data): _data(data)
    {
        for(size_t i = 0; i < SIZE_LABTOP; i++)
        {
            _cams[i] = CameraScene(tmp[i]);
        }
    }
    LabtopScene(){}

    void draw() override
    {
        _shockTimer -= _shockTimer ? 1 : 0;
        _rechargShock = _shockTimer ? 1 : 0;
        if(_visible)
        {
            _cams[_cam].draw();
            for(size_t i = 0; i < 1; i++)
            {
                if(_data->enemyPosition[i] == _cam)
                {
                    SDL_SetRenderDrawColor(renderer, _data->enemyFrame[i][_cam].color.r, _data->enemyFrame[i][_cam].color.g,
                                                     _data->enemyFrame[i][_cam].color.b, _data->enemyFrame[i][_cam].color.a);
                    SDL_RenderFillRect(renderer, &_data->enemyFrame[i][_cam].position);
                }
            }
            _data->energy -= 1;
        }
        return;
    }

    void switchCamera(size_t num){ _cam = num < SIZE_LABTOP ? num : _cam; }
    void useShock()
    {
        if(_cam == 6 && _rechargShock == 0)
        {
            if(_data->enemyPosition[0] == _cam)
            {
                _data->enemyPosition[0] = 0;
                _rechargShock = 1;
                _shockTimer = 300;
            }
        }
    }
private:
    bool _rechargShock = 0;
    size_t _shockTimer = 0;

    std::shared_ptr<nightDB> _data;
    std::array<CameraScene, SIZE_LABTOP> _cams;
    size_t _cam = 0;
};