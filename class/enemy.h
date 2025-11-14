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
    virtual int move() = 0;
    virtual bool attack(int doorStatus) = 0;

protected:
    virtual void rollback() = 0;
    virtual void killcam() = 0;

    shared_ptr<nightDB> _data;

    int _enemyPosition;
    bool _enemyActive = 0;

    size_t _timeOut = 0;
    size_t _timeWait = 0;
};

class SpringTime : public Enemy
{
private:
    void rollback() override
    {
        switch(_enemyPosition)
        {
            case(7): //0->7
                _enemyPosition = 0;
                break;
            case(9): //9->attack right
                _enemyPosition = 7;
                break;
            case(5): //5->6
                _enemyPosition = 7;
                break;
        }
    }

    void killcam() override
    {
    }
public:
    SpringTime(std::shared_ptr<nightDB> data)
    {
        _data = data;
        _enemyPosition = 0;
        _enemyActive = 1;
    }

    int move() override
    {
        if(_enemyActive && _enemyPosition != 10)
        {
            if(_timeOut * _data->night >=  500)
            {
                if(std::rand() % 10 >= 7){ rollback(); }
                switch(_enemyPosition)
                {
                    case(0): //0->7
                        _enemyPosition = 7;
                        break;
                    case(7): //7->5 || 7->9
                        if(std::rand() % 10 >= 11){ _enemyPosition = 5; }
                        else { _enemyPosition = 9; }
                        break;
                    case(9): //9->attack right
                        _enemyPosition = 10;
                        break;
                    case(5): //5->6
                        _enemyPosition = 6;
                        break;
                    case(6): //6-> do any && return
                        _data->energy = -3000.0;
                        _data->rechargEnergy = 1;
                        _enemyPosition = 0;
                        break;
                }

                _timeOut = 0;
            }
            _timeOut++;
        }
        return _enemyPosition;
    }

    bool attack(int doorStatus) override
    {
        if(_enemyPosition == 10)
        {
            if(_timeWait >= 500 + std::rand() % (7200 / _data->night))
            {
                if(doorStatus != 1)
                {
                    killcam();
                    return 0;
                }
                _enemyPosition = 0;

                _timeWait = 0;
            }
            _timeWait++;
        }

        _timeWait = 0;
        return 1;
    }
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