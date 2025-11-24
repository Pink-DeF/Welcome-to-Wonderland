#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <array>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>

#include "office.h"

using namespace GameConstant;
class Enemy
{
public:
    virtual int move(size_t enemyPosition) = 0;
    virtual bool attack(int doorStatus) = 0;

protected:
    virtual size_t calculatePosition(size_t enemyPosition) = 0;
    virtual size_t selectPosition(std::vector<std::pair<size_t, float>>& weights) =0;
    size_t _night = 0;
    std::shared_ptr<nightDB> _data;

    bool _enemyActive = 0;

    size_t _timeCooldawn = 0;
};

class SpringTime : public Enemy
{
private:
    size_t calculatePosition(size_t enemyPosition) override
    {
        std::vector<std::pair<size_t, float>> weights;

        switch(enemyPosition)
        {
            case 0:
                weights = { {4, 0.3f}, {7, 0.7f} };
                break;
            case 4:
                weights = { {0, 0.3f}, {5, 0.7f} };
                break;
            case 5:
                weights = { {4, 0.2f}, {6, 0.6f}, {9, 0.2f} };
                break;
            case 6:
                weights = { {0, 1.0f} };
                break;
            case 7:
                weights = { {0, 0.3f}, {9, 0.7f} };
                break;
            case 9:
                weights = { {10, 0.9f}, {6, 0.1f} };
                break;
            case 10:
                weights = { {0, 1.0f} };
                break;
            default:
                weights = { {0, 1.0f} };
                break;
        }
        return selectPosition(weights);
    }
    
    size_t selectPosition(std::vector<std::pair<size_t, float>>& weights) override 
    {
        return 0;
    }

public:
    SpringTime(std::shared_ptr<nightDB> data)
    {
        _data = data;
        _night = config.getNight();
        _enemyActive = 1;
    }

    int move(size_t enemyPosition) override
    {
        if(_enemyActive)
        {
            enemyPosition = calculatePosition(enemyPosition);
        }
        return enemyPosition;
    }

    bool attack(int doorStatus) override
    {
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