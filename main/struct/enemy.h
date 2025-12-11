#pragma once
#include <vector>

#include "../scene/office.h"

using namespace GameConstant;
class Enemy
{
public:
    virtual bool move(bool doorStatus) = 0;

protected:
    virtual void getMovePosition() = 0;
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
    size_t _ID = 10;

    size_t _moveCooldawn = 0;

    float _aggression = 0.1f;
    float _speed = 0.1f;
    size_t _basedCooldawn = 1000;
};