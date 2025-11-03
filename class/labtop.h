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
    LabtopScene(std::array<SDL_Color, SIZE_LABTOP> tmp, nightDB *data): _data(data)
    {
        for(size_t i = 0; i < SIZE_LABTOP; i++)
        {
            _cams[i] = CameraScene(tmp[i]);
        }
    }
    LabtopScene(){}

    void switchCamera(size_t num){ _cam = num < SIZE_LABTOP ? num : _cam; }
    void draw() override
    {
        if(_visible)
        {
            _cams[_cam].draw();
            _data->energy -= 1;
        }
        return;
    }
private:
    nightDB *_data;
    std::array<CameraScene, SIZE_LABTOP> _cams;
    size_t _cam = 0;
};