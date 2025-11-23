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
    private:
        void animate()
        {
            if(_timePar > 1.0 - TIME_PAR)
            { 
                _timePar = 0; 
                _closeAnimStatus = 0;

                _close.position.h = _closeStatus ? _height : 0;
            }
            else if(_closeAnimStatus)
            {
                _close.position.h += (int)(_height * _closeStatus - (_height * ! _closeStatus))* TIME_PAR;
                _timePar += TIME_PAR;
            }
        }

    public:
        _Door(){}
        _Door(object obj): _close(obj), _flash(obj), _height(obj.position.h)
        {
            _close.color.r = 255;
            _close.color.g = 0;
            _close.position.h = 0;

            _flash.color.r = 255;
            _flash.color.g = 255;
        }

        bool getStatus(){ return _closeStatus; }

        void draw()
        {
            animate();
            if(_closeStatus || _closeAnimStatus){ _close.draw(); }
            else if(_flashStatus){ _flash.draw(); }
        }

        void changeDoorStatus(size_t target)
        {
            if(!_closeAnimStatus)
            {
                bool tmp = _closeStatus;
                switch(target)
                {
                    case(0):
                        _closeStatus = _flashStatus = 0;
                        _closeAnimStatus = _closeStatus ? 1 : 0;
                        break;
                    case(1):
                        _closeStatus = _flashStatus == 0 ? !_closeStatus : _closeStatus;
                        _closeAnimStatus = tmp != _closeStatus ? 1 : 0;
                        break;
                    case(2):
                        _flashStatus = _closeStatus == 0 ? !_flashStatus : _flashStatus;
                        break;
                }
            }
        }

        float useEnergy()
        {
            return _flashStatus || _closeStatus ? -1.5 : 0;
        }

    private:
        size_t _height = 0;
        object _close;
        object _flash;

        bool inAnimation = 0;
        float _timePar = 0;

        bool _closeStatus = 0;
        bool _closeAnimStatus = 0;
        bool _flashStatus = 0;
    };
    //Методы связанные с вращением на пятой точке
    void move()
    {
        if(_timePar > 1.0 - TIME_PAR)
        { 
            _timePar = 0; 
            _cameraPosition = _cameraTargetPosition;
            _posViewport.x = -(_data->width * (_cameraPosition + 1));
        }
        else if(_cameraPosition != _cameraTargetPosition)
        {
            _posViewport.x -= (_data->width * _cameraTargetPosition - _data->width * _cameraPosition) * TIME_PAR;
            _timePar += TIME_PAR;
        }

        useParalax();
    }
    //Измение текстуры двери
    
    void calculateEnergy()
    {
        if(_visible)
        {
            _data->energy += _leftDoor.useEnergy() + _rightDoor.useEnergy() == 0 ? 3 : _leftDoor.useEnergy() + _rightDoor.useEnergy();
        }
    }
    void useParalax()
    {
        _paralax.currentPositionX = (_paralax.targetPositionX - _paralax.currentPositionX) * 0.7f;
        _paralax.currentPositionY = (_paralax.targetPositionX - _paralax.currentPositionY) * 0.7f;

        _viewport.x = _paralax.currentPositionX + static_cast<int>(_posViewport.x);
        _viewport.y = _paralax.currentPositionY + static_cast<int>(_posViewport.y);
    }

public:
    //Конструктор
    OfficeScene(){}
    OfficeScene(std::array<object, SIZE_OFFICE> &&tmp, std::shared_ptr<nightDB> data): _data(data)
    {
        _office = tmp;
        _leftDoor = _Door(tmp[1]);
        _rightDoor = _Door(tmp[2]);

        _posViewport = {-_data->width, 0, 3 * _data->width, _data->height};
        _viewport = {-_data->width, 0, 3 * _data->width, _data->height};
    }

    //Ппросто отрисовка
    void draw() override
    {
        if(_visible)
        {
            move();

            SDL_SetRenderViewport(renderer, &_viewport);
            for(size_t i = 0; i < SIZE_OFFICE; i++)
            {
                _office[i].draw();
            }
            _leftDoor.draw();
            _rightDoor.draw();

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
    void mouseMotion(SDL_MouseMotionEvent& motion)
    {
        if(_visible)
        {
            _paralax.targetPositionX = ((motion.x / (float)_data->width) * 2.0f - 1.0f) * PARALAX_INTENSITY * _data->width;
            _paralax.targetPositionY = ((motion.y / (float)_data->height) * 2.0f - 1.0f) * PARALAX_INTENSITY * _data->height;
        }
    }

private:
    std::shared_ptr<nightDB> _data;

    std::array<object,SIZE_OFFICE> _office;
    _Door _leftDoor;
    _Door _rightDoor;

    paralax _paralax;
    SDL_Rect _posViewport;
    SDL_Rect _viewport; 
    float _timePar = 0;
    int _cameraPosition = 0; 
    int _cameraTargetPosition = 0;
};