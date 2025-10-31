#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <array>
#include <cmath>
#include <memory>

#include "preset.h"

#define TIME_PAR 0.05
#define SIZE_OFFICE 3

class Enemy;

class OfficeScene : public Scene
{
public:
    //Конструктор
    OfficeScene(std::array<object, SIZE_OFFICE> &&tmp){ _objects = std::move(tmp); }

    //Методы связанные с вращением на пятой точке
    void changeCameraPosition(bool direct)
    {
        if(_visible && noMove())
        {
            if(direct)
            {
                _cameraTargetPosition = _cameraTargetPosition != 1 ? _cameraTargetPosition + 1 : _cameraTargetPosition;
                return;
            }        
            _cameraTargetPosition = _cameraTargetPosition != -1 ? _cameraTargetPosition - 1 : _cameraTargetPosition;
        }
    }
    bool noMove()
    {
        return _cameraPosition == _cameraTargetPosition ? 1 : 0;
    }
    int getCameraPosition(){ return _cameraPosition; }

    //Ппросто отрисовка
    float draw() override
    {
        if(_visible)
        {
            if(_timePar > 1.0){ _timePar = 0; _cameraPosition = _cameraTargetPosition; }
            else if(_cameraPosition != _cameraTargetPosition)
            {
                _viewport.x -= (width * _cameraTargetPosition - width * _cameraPosition) * TIME_PAR;
                _timePar += TIME_PAR;
            }

            SDL_SetRenderViewport(renderer, &_viewport);
            for(auto i: _objects)
            {
                SDL_SetRenderDrawColor(renderer, i.color.r, i.color.g, i.color.b, i.color.a);
                SDL_RenderFillRect(renderer, &(i.position));
            }
            return  (!_rightDoorStatus && !_leftDoorStatus ? 0.5 : 0) +
                    (_rightDoorStatus ? -1.5 : 0) +
                    (_leftDoorStatus ? -1.5 : 0);
        }
        return 0;
    }

    void openAll()
    {
        _leftDoorStatus = 0;
        _rightDoorStatus = 0;

        _objects[1].color.r = 0;
        _objects[1].color.g = 255;

        _objects[2].color.r = 0;
        _objects[2].color.g = 255;
    }
    void changeDoorStatus()
    {
        if(this->noMove())
        {
            size_t i;
            switch(_cameraPosition)
                {
                case(0):
                    return;
                case(1):
                    i = 2;
                    _rightDoorStatus = !_rightDoorStatus;
                    break;
                case(-1):
                    i = 1;
                    _leftDoorStatus = !_leftDoorStatus;
                    break;
                }
            auto tmp = _objects[i].color.r;
            _objects[i].color.r = _objects[i].color.g;
            _objects[i].color.g = tmp;
        }
    }

private:
    std::array<object, SIZE_OFFICE> _objects;

    bool _leftDoorStatus = 0;
    bool _rightDoorStatus = 0;

    SDL_Rect _viewport = {-width, 0, 3 * width, height};
    float _timePar = 0;
    int _cameraPosition = 0; 
    int _cameraTargetPosition = 0;
};