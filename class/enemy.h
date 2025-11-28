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
    virtual bool move(bool doorStatus) = 0;

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

    bool move(bool doorStatus) override
    {
        if(_enemyActive && _moveCooldawn > getMoveCooldawn() + rand() % 1000)
        {
            std::vector<std::pair<size_t, float>> weights;

            switch(_data->enemyPosition[0])
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
                    _data->enemyPosition[0] = 0;
                    break;
                case 7:
                    weights = { {0, 0.3f}, {9, 0.7f} };
                    break;
                case 9:
                    weights = { {10, 0.6f}, {7, 0.3f}, {6, 0.1f} };
                    for(auto i: _data->enemyPosition)
                    {
                        if(i == 10)
                        {
                            weights[1].second += weights[1].second / 2;
                            weights[2].second += weights[1].second / 2;
                            weights[0].second = 0.0f;
                            break;
                        }
                    }
                    break;
                case 10:
                    _data->enemyPosition[0] = 0;
                    return doorStatus;
                    break;
                default:
                    weights = { {0, 1.0f} };
                    break;
            }

            _moveCooldawn = 0;
            _data->enemyPosition[0] = selectPosition(weights, _data->enemyPosition[0]);
        }
        else { _moveCooldawn++; }

        return 1; 
    }
};

class ErrorTime : public Enemy
{
public:
    ErrorTime(std::shared_ptr<nightDB> data)
    {
        _data = data;
        _enemyActive = config.getNight() > 1 ? 1 : 0;

        _aggression = 0.1f;
        _speed = 0.7f;
        setupNightParameters();
    }

    void joke()
    {
        size_t random = static_cast<size_t>(rand() % 100);
        switch(random)
        {
            case(1):
                _data->invertTime = 300;
                break;
        }
    }

    bool move(bool doorStatus) override
    {
        if(_enemyActive)
        {
            if(_data->enemyPosition[1] == 10 && doorStatus){ return 0; }
            else if(_moveCooldawn > getMoveCooldawn() + rand() % 1000)
            {
                std::vector<std::pair<size_t, float>> weights;

                switch(_data->enemyPosition[1])
                {
                    case 0:
                        weights = { {4, 0.3f}, {7, 0.7f} };
                        break;
                    case 4:
                        weights = { {0, 0.3f}, {5, 0.7f} };
                        break;
                    case 5:
                        weights = { {4, 0.2f}, {9, 0.2f} };
                        break;
                    case 7:
                        weights = { {0, 0.3f}, {9, 0.7f} };
                        break;
                    case 9:
                        weights = { {10, 0.6f}, {7, 0.3f} };
                        for(auto i: _data->enemyPosition)
                        {
                            if(i == 10)
                            {
                                weights[1].second += weights[1].second / 2;
                                weights[2].second += weights[1].second / 2;
                                weights[0].second = 0.0f;
                                break;
                            }
                        }
                        break;
                    case 10:
                        weights = { {0, 1.0f} };
                        break;
                    default:
                        weights = { {0, 1.0f} };
                        break;
                }

                _moveCooldawn = 0;
                _data->enemyPosition[1] = selectPosition(weights, _data->enemyPosition[1]);
            }
            else
            {
                _moveCooldawn++;
                joke();
            }
        }
        return 1; 
    }
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