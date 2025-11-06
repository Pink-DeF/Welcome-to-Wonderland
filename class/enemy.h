#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <array>
#include <cmath>
#include <ctime>
#include <cstdlib>

#include "office.h"
using namespace std;

class Enemy
{
public:
    virtual void move() = 0;
    virtual void attack() = 0;
    virtual void killcam() = 0;

protected:
    nightDB *_data;

    bool _doorStatus = 0;
    bool _enemyActive = 0;

    size_t _timeOut = 0;
    size_t _timeWait = 0;
};

class SpringTime : public Enemy
{
public:
    SpringTime(nightDB *data): _numPos(0)
    {
        _data = data;
        _data->enemyPosition[_numPos] = 0;
        _enemyActive = 1;
    }
    void move() override
    {
        if(_enemyActive)
        {
            if(_timeOut * _data->night >= std::rand() % 10)
            {
                switch(_data->enemyPosition[_numPos])
                {
                    case(100):
                        _doorStatus = 1;
                        attack();
                        break;
                    case(0): //0->7
                        _data->enemyPosition[_numPos]= 7;
                        break;
                    case(7): //7->5 || 7->9
                        if(_data->monitorTime / _data->nightTime >= 0.3f){ _data->enemyPosition[_numPos] = 5; }
                        else { _data->enemyPosition[_numPos] = 9; }
                        break;
                    case(9): //9->attack right
                        _data->enemyPosition[_numPos] = 100;
                        _doorStatus = 1;
                        break;
                    case(5): //5->6
                        _data->enemyPosition[_numPos] = 6;
                        break;
                    case(6): //6-> do any && return
                        _data->enemyPosition[_numPos] = 0;
                        break;
                }

                _timeOut = (_data->monitorTime - _data->nightTime) % 100;
            }
            _timeOut++;
        }
    }

    void attack() override
    {
        if(_doorStatus == 1)
        {
            if(_timeWait >= 50 + std::rand() % (7200 / _data->night))
            {
                if(_data->rightDoorStatus == 0)
                {
                    _data->live = 0;
                    killcam();
                }
                _data->enemyPosition[_numPos] = 0;
                _doorStatus = 0;
            }
            _timeWait += _doorStatus == 1 ? 1 : -_timeWait;
        }
    }

    void killcam() override
    {

    }

private:
    const size_t _numPos;
};

/*
class ErrorTime : public Enemy
{
public:
    ErrorTime()
    {
    }

    void move(size_t nightTime, size_t labtopTime) override
    {

    }

private:

};

class MasterOfPuppet : public Enemy
{
public:
    MasterOfPuppet()
    {
    }
    size_t move() override {}

private:

};

class FoxDen : public Enemy
{
public:
    FoxDen()
    {
    }
    size_t move() override {}

private:
};
*/