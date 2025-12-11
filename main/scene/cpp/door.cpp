#include "../office.h"

void OfficeScene::_Door::animate()
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

OfficeScene::_Door::_Door(){}
OfficeScene::_Door::_Door(std::shared_ptr<nightDB> data, size_t ID, float height, Texture textureD, Texture hall): _height(height), _data(data), _ID(ID), _textureDoor(textureD), _hall(hall){}

bool OfficeScene::_Door::getStatus(){ return _closeStatus; }
bool OfficeScene::_Door::getFlashStatus(){ return _flashStatus; }

void OfficeScene::_Door::draw()
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

void OfficeScene::_Door::changeDoorStatus(size_t target)
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

float OfficeScene::_Door::useEnergy()
{
    return _flashStatus || _closeStatus ? -1.5 : 0;
}