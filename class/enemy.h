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
    virtual void move(size_t nightTime, size_t labtopTime) = 0;

protected:
    size_t _night = 0;

    size_t _doorStatus = 0;
    bool _enemyActive = 0;

    size_t _enemyPosition;
    size_t _timeOut = 0;
};

class SpringTime : public Enemy
{
public:
    SpringTime(size_t night)
    {
        _enemyPosition = 0;
        _enemyActive = 1;
        _night = night;
    }
    void move(size_t nightTime, size_t labtopTime) override
    {
        srand(time(nullptr));
        if(_enemyActive)
        {
            if(_night * _timeOut >= std::rand() % 1000)
            {
                switch(_enemyPosition)
                {
                    case(0):
                        _enemyPosition = 7;
                        break;
                    case(7):
                        if(labtopTime / nightTime >= 0.5f){ _enemyPosition = 5; }
                        else { _enemyPosition = 9; }
                        break;
                    case(9):
                        _enemyPosition = 100;
                        _doorStatus = 1;
                        break;
                    case(5):
                        _enemyPosition = 6;
                        break;
                    case(6):
                        _enemyPosition = 0;
                        break;
                }

                _timeOut  = -labtopTime;
            }
            _timeOut++;
        }
    }

private:

};

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
/*

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