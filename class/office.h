#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <array>
#include <cmath>
#include <memory>
#include <iostream>

#include "preset.h"
#include "classes.h"

using namespace GameConstant;
class OfficeScene : public Scene
{
private:
    class _Door
    {
    public:
        _Door(){}
        _Door(object obj): _position(obj){}

        object getPosition(){ return _position; }
        bool getStatus(){ return _closeStatus; }

        void changeDoorStatus(size_t target)
        {
            switch(target)
            {
                case(0):
                    _closeStatus = _flashStatus = 0;
                    break;
                case(1):
                    _closeStatus = _flashStatus == 0 ? !_closeStatus : _closeStatus;
                    break;
                case(2):
                    _flashStatus = _closeStatus == 0 ? !_flashStatus : _flashStatus;
                    break;
            }
            changeDoorColor();
        }

        void changeDoorColor()
        {
            if(_flashStatus)
            {
                _position.color.r = 255;
                _position.color.g = 255;
            }
            else if(_closeStatus)
            {
                _position.color.r = 255;
                _position.color.g = 0;
            }
            else
            {
                _position.color.r = 0;
                _position.color.g = 255;
            }
        }

        float useEnergy()
        {
            return _flashStatus || _closeStatus ? -1.5 : 0;
        }

    private:
        object _position;

        bool _closeStatus = 0;
        bool _flashStatus = 0;
    };
    //Методы связанные с вращением на пятой точке
    void move()
    {
        if(_timePar > 1.0 - TIME_PAR)
        { 
            _timePar = 0; 
            _cameraPosition = _cameraTargetPosition;
            _viewport.x = -(_data->width * (_cameraPosition + 1));
        }
        else if(_cameraPosition != _cameraTargetPosition)
        {
            _viewport.x -= (_data->width * _cameraTargetPosition - _data->width * _cameraPosition) * TIME_PAR;
            _timePar += TIME_PAR;
        }
    }
    //Измение текстуры двери
    
    void calculateEnergy()
    {
        if(_visible)
        {
            _data->energy += _leftDoor.useEnergy() + _rightDoor.useEnergy() == 0 ? 3 : _leftDoor.useEnergy() + _rightDoor.useEnergy();
        }
    }
public:
    //Конструктор
    OfficeScene(){}
    OfficeScene(std::array<object, SIZE_OFFICE> &&tmp, std::shared_ptr<nightDB> data): _data(data)
    {
        _office = tmp[0];
        _leftDoor = _Door(tmp[1]);
        _rightDoor = _Door(tmp[2]);

        _viewport = {-_data->width, 0, 3 * _data->width, _data->height};
    }

    //Ппросто отрисовка
    void draw() override
    {
        if(_visible)
        {
            move();

            SDL_SetRenderViewport(renderer, &_viewport);
            _office.draw();
            _leftDoor.getPosition().draw();
            _rightDoor.getPosition().draw();

        }

        calculateEnergy();
        return;
    }

    //Geters
    int getCameraPosition(){ return _cameraPosition; }
    int getLeftDoorStatus(){ return _leftDoor.getStatus();}
    int getRightDoorStatus(){ return _rightDoor.getStatus();}
    bool noMove()
    {
        return _cameraPosition == _cameraTargetPosition ? 1 : 0;
    }

    //chengers
    void changeDoorStatus(size_t target)
    {
        if(noMove() && target <= 3)
        {
            switch(_cameraPosition)
            {
                case(-1):
                    _leftDoor.changeDoorStatus(target);
                    break;
                case(1):
                    _rightDoor.changeDoorStatus(target);
                    break;
            }
        }
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

    _Door _leftDoor;
    _Door _rightDoor;
    object _office;

    SDL_Rect _viewport; 
    float _timePar = 0;
    int _cameraPosition = 0; 
    int _cameraTargetPosition = 0;
};