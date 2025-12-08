#pragma once
#include <memory>

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

                _textureDoor.position.h = _closeStatus ? _height : 0;
            }
            else if(_closeAnimStatus)
            {
                _textureDoor.position.h += static_cast<int>(_height * _closeStatus - (_height * ! _closeStatus)) * TIME_PAR;
                _timePar += TIME_PAR;
            }
        }

    public:
        _Door(){}
        _Door(std::shared_ptr<nightDB> data, size_t ID, float height, Texture textureD, Texture hall): _height(height), _data(data), _ID(ID), _textureDoor(textureD), _hall(hall){}

        bool getStatus(){ return _closeStatus; }
        bool getFlashStatus(){ return _flashStatus; }

        void draw()
        {
            animate();
            if(_closeStatus || _closeAnimStatus){ _textureDoor.draw(); }
            else if(_flashStatus){ _hall.draw(); }

            if(_flashStatus)
            {
                for(size_t i = 0; i < ENEMY_COUNT; i++)
                {
                    if(_data->enemyPosition[i] == _ID)
                    {
                        _data->enemyDoorTexture[i].draw();
                        return;
                    }
                }

            }
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
                        _closeAnimStatus = tmp != _closeStatus ? 1 : 0;
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
        std::shared_ptr<nightDB> _data;
        Texture _hall = {};
        Texture _textureDoor = {};
        size_t _ID = 0;

        size_t _height = 0;

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
            _posViewport.x = -(static_cast<int>(config.getWidth()) * (_cameraPosition + 1));
        }
        else if(_cameraPosition != _cameraTargetPosition)
        {
            _posViewport.x -= (config.getWidth() * _cameraTargetPosition - config.getWidth() * _cameraPosition) * TIME_PAR;
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
        _paralax.currentPositionY = (_paralax.targetPositionY - _paralax.currentPositionY) * 0.7f;

        _viewport.x = -_paralax.currentPositionX + static_cast<int>(_posViewport.x);
        _viewport.y = -_paralax.currentPositionY + static_cast<int>(_posViewport.y);
    }

public:
    //Конструктор
    OfficeScene(){}
    OfficeScene(std::shared_ptr<nightDB> data): _data(data)
    { _viewport = _posViewport = {-config.getWidth(), 0, 3 * config.getWidth(), config.getHeight()}; }

    //Ппросто отрисовка
    void draw() override
    {
        _data->invertTime -= _data->invertTime != 0 ? 1 : 0;
        _invertControl = _data->invertTime != 0 ? 1 : 0;
        if(_visible)
        {
            move();

            SDL_SetRenderViewport(renderer, &_viewport);

            _office.draw();
            _leftDoor.draw();
            _rightDoor.draw();
        }

        calculateEnergy();
        return;
    }

    //Geters
    bool getLeftDoorStatus(){ return _leftDoor.getStatus();}
    bool getRightDoorStatus(){ return _rightDoor.getStatus();}

    bool getLeftDoorFlash(){ return _leftDoor.getFlashStatus();}
    bool getRightDoorFlash(){ return _rightDoor.getFlashStatus();}

    int getCameraPosition(){ return _cameraPosition; }
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
            if((direct + _invertControl) % 2)
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
            _paralax.targetPositionX = ((motion.x /static_cast<float>(config.getWidth())) * 2.0f - 1.0f) * PARALAX_INTENSITY * config.getWidth();
            _paralax.targetPositionY = ((motion.y / static_cast<float>(config.getHeight())) * 2.0f - 1.0f) * PARALAX_INTENSITY * config.getHeight();
        }
    }

private:
    std::shared_ptr<nightDB> _data;

    Texture _office = Texture{IMG_LoadTexture(renderer, "Texture/office.jpg"),
            SDL_FRect{0, 0, static_cast<float>(config.getWidth())* 3, static_cast<float>(config.getHeight())},
            SDL_FRect{0, 0, 3072, 800}};

    _Door _leftDoor = _Door(_data, 11, static_cast<float>(config.getHeight()) * 5 / 10,
            Texture{IMG_LoadTexture(renderer, "Texture/leftDoor.jpg"),
            SDL_FRect{0, static_cast<float>(config.getHeight()) / 10, static_cast<float>(config.getWidth()) * 2 / 5, 0},
            SDL_FRect{50, 0, 800, 900}},
            Texture{IMG_LoadTexture(renderer, "Texture/leftFlash.png"),
            SDL_FRect{0, static_cast<float>(config.getHeight()) / 10, static_cast<float>(config.getWidth()) * 2 / 5, static_cast<float>(config.getHeight()) * 4 / 10},
            SDL_FRect{0, 0, 960, 934}});
    _Door _rightDoor = _Door(_data, 10, static_cast<float>(config.getHeight()) * 9 / 10,
            Texture{IMG_LoadTexture(renderer, "Texture/rightDoor.jpg"),
            SDL_FRect{static_cast<float>(config.getWidth()) * 13 / 5, static_cast<float>(config.getHeight()) / 10, static_cast<float>(config.getWidth()) * 2 / 5, 0},
            SDL_FRect{0, 0, 700, 1400}},
            Texture{IMG_LoadTexture(renderer, "Texture/rightFlash.jpg"),
            SDL_FRect{static_cast<float>(config.getWidth()) * 13 / 5, static_cast<float>(config.getHeight()) * 2 / 10, static_cast<float>(config.getWidth()) * 2 / 5, static_cast<float>(config.getHeight()) * 6 / 10},
            SDL_FRect{0, 0, 960, 934}});

    paralax _paralax;
    SDL_Rect _posViewport;
    SDL_Rect _viewport; 

    bool _invertControl = 0;

    float _timePar = 0;
    int _cameraPosition = 0; 
    int _cameraTargetPosition = 0;
};