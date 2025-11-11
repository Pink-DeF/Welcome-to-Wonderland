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
private:
    //Методы связанные с вращением на пятой точке
    void move()
    {
        if(_timePar > 1.0){ _timePar = 0; _cameraPosition = _cameraTargetPosition; }
        else if(_cameraPosition != _cameraTargetPosition)
        {
            _viewport.x -= (width * _cameraTargetPosition - width * _cameraPosition) * TIME_PAR;
            _timePar += TIME_PAR;
        }
    }
    //Измение текстуры двери
    void changeDoorColor()
    {
        if(_leftFlesh)
        {
            _objects[1].color.r = 255;
            _objects[1].color.g = 255;
        }
        else if(_data->leftDoorStatus)
        {
            _objects[1].color.r = 255;
            _objects[1].color.g = 0;
        }
        else
        {
            _objects[1].color.r = 0;
            _objects[1].color.g = 255;
        }

        if(_rightFlesh)
        {
            _objects[2].color.r = 255;
            _objects[2].color.g = 255;
        }
        else if(_data->rightDoorStatus)
        {
            _objects[2].color.r = 255;
            _objects[2].color.g = 0;
        }
        else
        {
            _objects[2].color.r = 0;
            _objects[2].color.g = 255;
        }
    }
    
    void calculateEnergy()
    {
        if(_data->rightDoorStatus + _leftFlesh + _data->leftDoorStatus + _rightFlesh == 0 && _visible){ _data->energy += 3; }
        else
        {
            _data->energy += _data->rightDoorStatus || _leftFlesh ? -1.5 : 0;
            _data->energy += _data->leftDoorStatus || _rightFlesh ? -1.5 : 0;
        }
    }
public:
    //Конструктор
    OfficeScene(std::array<object, SIZE_OFFICE> &&tmp, nightDB *data): _data(data) { _objects = std::move(tmp); }

    //Ппросто отрисовка
    void draw() override
    {
        if(_visible)
        {
            move();

            SDL_SetRenderViewport(renderer, &_viewport);
            for(auto i: _objects)
            {
                SDL_SetRenderDrawColor(renderer, i.color.r, i.color.g, i.color.b, i.color.a);
                SDL_RenderFillRect(renderer, &(i.position));
            }

        }

        calculateEnergy();
        return;
    }

    //Geters
    int getCameraPosition(){ return _cameraPosition; }
    bool noMove()
    {
        return _cameraPosition == _cameraTargetPosition ? 1 : 0;
    }

    //chengers
    void openAll()
    {
        _data->leftDoorStatus = 0;
        _data->rightDoorStatus = 0;

        _leftFlesh = 0;
        _rightFlesh = 0;
        
        changeDoorColor();
    }
    void changeDoorStatus()
    {
        if(noMove())
        {
            switch(_cameraPosition)
                {
                case(-1):
                    _data->leftDoorStatus = _leftFlesh == 0 ? !_data->leftDoorStatus : _data->leftDoorStatus;
                    break;
                case(1):
                    _data->rightDoorStatus = _rightFlesh == 0 ? !_data->rightDoorStatus : _data->rightDoorStatus;
                    break;
                }
        }
        changeDoorColor();
    }

    void useDoorFlesh()
    {
        if(noMove())
        {
            switch(_cameraPosition)
            {
                case(-1):
                    _leftFlesh = _data->leftDoorStatus == 0 ? !_leftFlesh : _leftFlesh;
                    break;
                case(1):
                    _rightFlesh = _data->rightDoorStatus == 0 ? !_rightFlesh : _rightFlesh;
                    break;
            }
        }
        changeDoorColor();
    }

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
private:
    nightDB *_data;
    std::array<object, SIZE_OFFICE> _objects;

    bool _leftFlesh= 0;
    bool _rightFlesh = 0;

    SDL_Rect _viewport = {-width, 0, 3 * width, height};
    float _timePar = 0;
    int _cameraPosition = 0; 
    int _cameraTargetPosition = 0;
};