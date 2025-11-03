#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <array>
#include <cmath>
#include <memory>

#include "preset.h"

#define TIME_PAR 0.05
#define SIZE_OFFICE 3

class OfficeScene : public Scene
{
public:
    //Конструктор
    OfficeScene(std::array<object, SIZE_OFFICE> &&tmp, nightDB *data): _data(data) { _objects = std::move(tmp); }

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
    void draw() override
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

            if(!_data->rightDoorStatus && !_data->leftDoorStatus) { _data->energy += 0.5; }
            else
            {
                _data->energy += _data->rightDoorStatus ? -1.5 : 0;
                _data->energy += _data->leftDoorStatus ? -1.5 : 0;
            }
        }
        return;
    }

    void openAll()
    {
        _data->leftDoorStatus = 0;
        _data->rightDoorStatus = 0;

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
                    _data->rightDoorStatus = !_data->rightDoorStatus;
                    break;
                case(-1):
                    i = 1;
                    _data->leftDoorStatus = !_data->leftDoorStatus;
                    break;
                }
            auto tmp = _objects[i].color.r;
            _objects[i].color.r = _objects[i].color.g;
            _objects[i].color.g = tmp;
        }
    }

private:
    nightDB *_data;
    std::array<object, SIZE_OFFICE> _objects;

    SDL_Rect _viewport = {-width, 0, 3 * width, height};
    float _timePar = 0;
    int _cameraPosition = 0; 
    int _cameraTargetPosition = 0;
};