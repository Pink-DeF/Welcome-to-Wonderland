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
    virtual void setupNightParameters()
    {
        _aggression = std::min(0.1f + (config.getNight()- 1) * 0.15f, 0.9f);
        _speed = std::min(0.1f + (config.getNight()- 1) * 0.15f, 0.9f);
    }

    size_t getMoveCooldawn() { return static_cast<int>(_basedCooldawn / _speed); }

    std::shared_ptr<nightDB> _data;

    bool _enemyActive = 0;

    size_t _moveCooldawn = 0;
    size_t _cameraAttackTimer = 0;
    size_t _attackTimer = 0;

    float _aggression = 0.1f;
    float _speed = 0.1f;
    size_t _basedCooldawn = 1000;
};

class SpringTime : public Enemy
{
private:
    size_t calculatePosition(size_t enemyPosition) override
    {
        std::vector<std::pair<size_t, float>> weights;
        size_t curDist = _data->_distanceToOffice[enemyPosition];

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

        for(auto [position, weight]: weights)
        {
            size_t newDist = _data->_distanceToOffice[position];
            if(newDist < curDist) { weight *= 1.0f + _aggression; }
            else if(newDist > curDist) { weight *= 1.0f - _aggression; }
        }
        return selectPosition(weights);
    }
    
    size_t selectPosition(std::vector<std::pair<size_t, float>>& weights) override 
    {
        float totalWeight = 0.0f;
        for(auto i: weights){ totalWeight += i.second; }

        float random = static_cast<float>(rand()) / RANDOM_MAX * totalWeight;
        float camulative = 0.0f;
    
        for(auto i: weights)
        {
            camulative += i.second;
            if(random <= camulative){ return i.first; }
        }
        return weights.back().first;
    }

    void attackSystem()
    {
        if(_cameraAttackTimer > 1000 + rand() % (4000 / config.getNight()))
        {
            _data->energy = -3000;
            _cameraAttackTimer = 0;
        }
        _cameraAttackTimer++;
    }

public:
    SpringTime(std::shared_ptr<nightDB> data)
    {
        _data = data;
        _enemyActive = 1;
        setupNightParameters();
    }

    int move(size_t enemyPosition) override
    {
        if(enemyPosition == 6)
        {
            attackSystem();
            return enemyPosition;
        }
        else if(_enemyActive && _moveCooldawn > getMoveCooldawn() + rand() % 1000)
        {
            enemyPosition = calculatePosition(enemyPosition);
            _moveCooldawn = _attackTimer = _cameraAttackTimer = 0;

            return enemyPosition;
        }

        _moveCooldawn++;
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