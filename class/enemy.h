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

protected:
    virtual void rollback() = 0;
    virtual void attack() = 0;
    virtual void killcam() = 0;

    nightDB *_data;

    bool _enemyActive = 0;

    size_t _timeOut = 0;
    size_t _timeWait = 0;
};

class SpringTime : public Enemy
{
private:
    void attack() override
    {
        if(_timeWait >= 50 + std::rand() % (7200 / _data->night))
        {
            if(_data->rightDoorStatus == 0)
            {
                killcam();
                _data->live = 0;
            }
            _data->enemyPosition[_numPos] = 0;

            _timeWait = 0;
        }
        _timeWait++;
    }

    void rollback() override
    {
        switch(_data->enemyPosition[_numPos])
        {
            case(7): //0->7
                _data->enemyPosition[_numPos] = 0;
                break;
            case(9): //9->attack right
                _data->enemyPosition[_numPos] = 7;
                break;
            case(5): //5->6
                _data->enemyPosition[_numPos] = 7;
                break;
        }
    }

    void killcam() override
    {
    }
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
            if(_data->enemyPosition[_numPos] == 10){ attack(); }
            if(_timeOut * _data->night >=  1000)
            {
                if(std::rand() % 10 >= 7){ rollback(); }
                switch(_data->enemyPosition[_numPos])
                {
                    case(0): //0->7
                        _data->enemyPosition[_numPos]= 7;
                        break;
                    case(7): //7->5 || 7->9
                        if(std::rand() % 10 >= 0){ _data->enemyPosition[_numPos] = 5; }
                        else { _data->enemyPosition[_numPos] = 9; }
                        break;
                    case(9): //9->attack right
                        _data->enemyPosition[_numPos] = 10;
                        break;
                    case(5): //5->6
                        _data->enemyPosition[_numPos] = 6;
                        break;
                    case(6): //6-> do any && return
                        _data->energy = -3000.0;
                        _data->rechargEnergy = 1;
                        _data->enemyPosition[_numPos] = 0;
                        break;
                }

                _timeOut = (_data->monitorTime - _data->nightTime) % 100;
            }
            _timeOut++;
        }
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