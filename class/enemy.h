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
    virtual std::pair<bool, size_t> move(bool doorStatus, size_t enemyPosition) = 0;

protected:
    size_t selectPosition(std::vector<std::pair<size_t, float>>& weights, size_t enemyPosition)
    {
        size_t curDist = _data->_distanceToOffice[enemyPosition];
        for(auto [position, weight]: weights)
        {
            size_t newDist = _data->_distanceToOffice[position];
            if(newDist < curDist) { weight *= 1.0f + _aggression; }
            else if(newDist > curDist) { weight *= 1.0f - _aggression; }
        }

        float totalWeight = 0.0f;
        for(auto i: weights){ totalWeight += i.second; }
        if(totalWeight == 0.0f){ return enemyPosition; }

        float random = static_cast<float>(rand() % RAND_MAX) / static_cast<float>(RAND_MAX) * totalWeight;
        float camulative = 0.0f;
    
        for(auto i: weights)
        {
            camulative += i.second;
            if(random <= camulative){ return i.first; }
        }
        return weights.back().first;
    }

    virtual void setupNightParameters()
    {
        _aggression = std::min(_aggression + (config.getNight()- 1) * 0.15f, 0.9f);
        _speed = std::min(_speed + (config.getNight()- 1) * 0.15f, 0.9f);
    }

    size_t getMoveCooldawn() { return static_cast<size_t>(_basedCooldawn / _speed); }

    std::shared_ptr<nightDB> _data;

    bool _enemyActive = 0;

    size_t _moveCooldawn = 0;

    float _aggression = 0.1f;
    float _speed = 0.1f;
    size_t _basedCooldawn = 1000;
};

class SpringTime : public Enemy
{
public:
    SpringTime(std::shared_ptr<nightDB> data)
    {
        _data = data;
        _enemyActive = 1;

        _aggression = 0.5f;
        _speed = 0.3f;
        setupNightParameters();
    }

    std::pair<bool, size_t> move(bool doorStatus, size_t enemyPosition) override
    {
        //std::cout<<doorStatus<<std::endl;
        if(_enemyActive && _moveCooldawn > getMoveCooldawn() + rand() % 1000)
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
                    _data->energy = -3000;
                    enemyPosition = 0;
                    break;
                case 7:
                    weights = { {0, 0.3f}, {9, 0.7f} };
                    break;
                case 9:
                    weights = { {10, 0.9f}, {6, 0.1f} };
                    break;
                case 10:
                    enemyPosition = 0;
                    return std::pair<bool, size_t>(doorStatus, enemyPosition);
                    break;
                default:
                    weights = { {0, 1.0f} };
                    break;
            }

            _moveCooldawn = 0;
            enemyPosition = selectPosition(weights, enemyPosition);
        }
        else { _moveCooldawn++; }

        return std::pair<bool, size_t>(1, enemyPosition);
    }
};


/*
class ErrorTime : public Enemy
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

        return selectPosition(weights, enemyPosition);
    }

    size_t attackSystem(size_t enemyPosition)
    {
        if(_cameraAttackTimer > 1000 + rand() % (4000 / config.getNight()))
        {
            _data->energy = -3000;
            _cameraAttackTimer = 0;
            enemyPosition = 0;
        }
        _cameraAttackTimer++;

        return enemyPosition;
    }

    bool attack(size_t& enemyPosition, bool& doorStatus) override
    {
        if(enemyPosition == 10)
        {
            if(_attackTimer > getMoveCooldawn() + rand() % 1000)
            {
                return doorStatus;
            }
            _attackTimer++;
        }
        return 1;
    }

public:
    ErrorTime(std::shared_ptr<nightDB> data)
    {
        _data = data;
        _enemyActive = config.getNight() > 1 ? 1 : 0;

        _aggression = 0.1f;
        _speed = 0.5f;
        setupNightParameters();
    }

    std::pair<bool, size_t> move(bool doorStatus, size_t enemyPosition) override
    {
        switch(enemyPosition)
        {
            case(6):
                attackSystem(enemyPosition);
                break;
            case(10):
                attack(enemyPosition, doorStatus);
                break;
            default:
                if(_enemyActive && _moveCooldawn > getMoveCooldawn() + rand() % 1000)
                {
                    enemyPosition = calculatePosition(enemyPosition);
                    _moveCooldawn = _attackTimer = _cameraAttackTimer = 0;
                }
                else { _moveCooldawn++; }
                break;
        }

        return std::pair<bool, size_t>(1, enemyPosition);
    }
};
*/
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