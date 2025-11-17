#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <array>
#include <cmath>
#include <memory>

#include "preset.h"
#include "classes.h"

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
            _viewport.x -= (_data->width * _cameraTargetPosition - _data->width * _cameraPosition) * TIME_PAR;
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
        else if(_leftDoorStatus)
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
        else if(_rightDoorStatus)
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
        if(_rightDoorStatus + _leftFlesh + _leftDoorStatus + _rightFlesh == 0 && _visible){ _data->energy += 3; }
        else
        {
            _data->energy += _rightDoorStatus || _leftFlesh ? -1.5 : 0;
            _data->energy += _leftDoorStatus || _rightFlesh ? -1.5 : 0;
        }
    }
public:
    //Конструктор
    OfficeScene(std::array<object, SIZE_OFFICE> &&tmp, std::shared_ptr<nightDB> data): _data(data) { _objects = std::move(tmp); }

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
    int getLeftDoorStatus(){ return _leftDoorStatus ? 1 : 0;}
    int getRightDoorStatus(){ return _rightDoorStatus ? 1 : 0;}
    bool noMove()
    {
        return _cameraPosition == _cameraTargetPosition ? 1 : 0;
    }

    //chengers
    void openAll()
    {
        _leftDoorStatus = 0;
        _rightDoorStatus = 0;

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
                    _leftDoorStatus = _leftFlesh == 0 ? !_leftDoorStatus : _leftDoorStatus;
                    break;
                case(1):
                    _rightDoorStatus = _rightFlesh == 0 ? !_rightDoorStatus : _rightDoorStatus;
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
                    _leftFlesh = _leftDoorStatus == 0 ? !_leftFlesh : _leftFlesh;
                    break;
                case(1):
                    _rightFlesh = _rightDoorStatus == 0 ? !_rightFlesh : _rightFlesh;
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
    std::shared_ptr<nightDB> _data;
    std::array<object, SIZE_OFFICE> _objects;

    bool _leftDoorStatus = 0;
    bool _rightDoorStatus = 0;

    bool _leftFlesh= 0;
    bool _rightFlesh = 0;

    SDL_Rect _viewport = {-_data->width, 0, 3 * _data->width, _data->height};
    float _timePar = 0;
    int _cameraPosition = 0; 
    int _cameraTargetPosition = 0;
};