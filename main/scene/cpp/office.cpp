#include "../office.h"

//Методы связанные с вращением на пятой точке
void OfficeScene::move()
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

void OfficeScene::calculateEnergy()
{
    if(_visible)
    {
        _data->energy += _leftDoor.useEnergy() + _rightDoor.useEnergy() == 0 ? 3 : _leftDoor.useEnergy() + _rightDoor.useEnergy();
    }
}
void OfficeScene::useParalax()
{
    _paralax.currentPositionX = (_paralax.targetPositionX - _paralax.currentPositionX) * 0.7f;
    _paralax.currentPositionY = (_paralax.targetPositionY - _paralax.currentPositionY) * 0.7f;

    _viewport.x = -_paralax.currentPositionX + static_cast<int>(_posViewport.x);
    _viewport.y = -_paralax.currentPositionY + static_cast<int>(_posViewport.y);
}

//Ппросто отрисовка
void OfficeScene::draw()
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
bool OfficeScene::getLeftDoorStatus(){ return _leftDoor.getStatus();}
bool OfficeScene::getRightDoorStatus(){ return _rightDoor.getStatus();}

bool OfficeScene::getLeftDoorFlash(){ return _leftDoor.getFlashStatus();}
bool OfficeScene::getRightDoorFlash(){ return _rightDoor.getFlashStatus();}

int OfficeScene::getCameraPosition(){ return _cameraPosition; }
bool OfficeScene::noMove()
{
    return _cameraPosition == _cameraTargetPosition ? 1 : 0;
}

//chengers
void OfficeScene::changeDoorStatus(size_t target)
{
    if(target == 0)
    {
        _leftDoor.changeDoorStatus(target);
        _rightDoor.changeDoorStatus(target);
    }
    else if(noMove() && target <= 3)
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

void OfficeScene::changeCameraPosition(bool direct)
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
void OfficeScene::mouseMotion(SDL_MouseMotionEvent& motion)
{
    if(_visible)
    {
        _paralax.targetPositionX = ((motion.x /static_cast<float>(config.getWidth())) * 2.0f - 1.0f) * PARALAX_INTENSITY * config.getWidth();
        _paralax.targetPositionY = ((motion.y / static_cast<float>(config.getHeight())) * 2.0f - 1.0f) * PARALAX_INTENSITY * config.getHeight();
    }
}