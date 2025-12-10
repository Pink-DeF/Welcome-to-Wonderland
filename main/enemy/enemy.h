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
    void jumpscare()
    {

    }
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

class SpringTime : public Enemy
{
private:
    void getMovePosition() override
    {
        std::vector<std::pair<size_t, float>> weights;

        switch(_data->enemyPosition[_ID])
        {
            case 0:
                weights = { {5, 0.3f}, {7, 0.7f} };
                break;
            case 5:
                weights = { {6, 0.6f}, {9, 0.2f} };
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
                        weights[1].second += weights[0].second / 2;
                        weights[2].second += weights[0].second / 2;
                        weights[0].second = 0.0f;
                        break;
                    }
                }
                break;
            default:
                weights = { {0, 1.0f} };
                break;
        }

        _data->enemyPosition[_ID] = selectPosition(weights, _data->enemyPosition[0]);
    }

public:
    SpringTime(std::shared_ptr<nightDB> data, size_t ID)
    {
        _ID = ID;
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
            _moveCooldawn = 0;
            if(_data->enemyPosition[_ID] == 10)
            {
                _data->enemyPosition[_ID] = 0;
                return doorStatus;
            }
            getMovePosition();
        }
        else { _moveCooldawn++; }

        return 1; 
    }
};

class ErrorTime : public Enemy
{
private:
    void getMovePosition() override
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
                weights = { {11, 0.6f}, {7, 0.3f} };
                for(auto i: _data->enemyPosition)
                {
                    if(i == 11)
                    {
                        weights[1].second += weights[0].second;
                        weights[0].second = 0.0f;
                        break;
                    }
                }
                break;
            case 11:
                weights = { {0, 1.0f} };
                break;
            default:
                weights = { {0, 1.0f} };
                break;
        }

        _data->enemyPosition[_ID] = selectPosition(weights, _data->enemyPosition[1]);
    }

public:
    ErrorTime(std::shared_ptr<nightDB> data, size_t ID)
    {
        _ID = ID;
        _data = data;
        _enemyActive = config.getNight() > 2 ? 1 : 0;

        _aggression = 0.1f;
        _speed = 0.5f;
        setupNightParameters();
    }

    void joke()
    {
        size_t random = static_cast<size_t>(rand() % 10000);
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
            if(_data->enemyPosition[_ID] == 11 && doorStatus){ return 0; }
            else if(_moveCooldawn > getMoveCooldawn() + rand() % 1000)
            {
                _moveCooldawn = 0;
                getMovePosition();
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

class FoxDen : public Enemy
{
private:
    void getMovePosition() override
    {
        std::vector<std::pair<size_t, float>> weights;

        switch(_data->enemyPosition[1])
        {
            case 3:
                weights = { {11, 0.5f}, {3, 0.5f} };
                for(auto i: _data->enemyPosition)
                {
                    if(i == 11)
                    {
                        weights[1].second += weights[0].second;
                        weights[0].second = 0.0f;
                        break;
                    }
                }
                break;
                break;
            case 4:
                weights = { {9, 0.3f}, {8, 0.7f} };
                break;
            case 8:
                weights = { {3, 0.7f}, {4, 0.3f} };
                break;
            case 9:
                weights = { {4, 0.2f}, {8, 0.2f} };
                break;
            default:
                weights = { {4, 1.0f} };
                break;
        }

        _data->enemyPosition[_ID] = selectPosition(weights, _data->enemyPosition[1]);
    }
public:
    FoxDen(std::shared_ptr<nightDB> data, size_t ID)
    {
        _ID = ID;
        _data = data;
        _enemyActive = config.getNight() > 1 ? 1 : 0;

        _aggression = 0.5f;
        _speed = 0.7f;
        setupNightParameters();
    }


    void doubleJump()
    {
        if((_data->enemyPosition[_ID] != 10 && _data->enemyPosition[_ID] != 11) && rand() % 1 <= 0.2f)
        {
            getMovePosition();
        }
    }

    bool move(bool doorStatus) override
    {
        if(_enemyActive)
        {
            if(_moveCooldawn > getMoveCooldawn() + rand() % 1000)
            {
                _moveCooldawn = 0;
                if(_data->enemyPosition[_ID] == 11)
                {
                    _data->enemyPosition[_ID] = 0;
                    return doorStatus;
                }
                getMovePosition();
                doubleJump();
            }
            else
            {
                _moveCooldawn++;
            }
        }
        return 1; 
    }
};

class MasterOfPuppet : public Enemy
{
private:
    void getMovePosition() override
    {
        std::vector<std::pair<size_t, float>> weights;

        switch(_data->enemyPosition[1])
        {
            case 3:
                weights = { {8, 0.8f}, {5, 0.2f} };
                break;
            case 7:
                weights = { {3, 0.5f}, {8, 0.3f}, {5, 0.2f} };
                break;
            case 8:
                weights = { {7, 0.8f}, {5, 0.2f} };
                break;
            case 5:
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
            default:
                weights = { {3, 1.0f} };
                break;
        }

        _data->enemyPosition[_ID] = selectPosition(weights, _data->enemyPosition[1]);
    }

    void useFake()
    {
        _data->MasterFakePosition = static_cast<size_t>(rand() % 30);
    }

public:
    MasterOfPuppet(std::shared_ptr<nightDB> data, size_t ID)
    {
        _ID = ID;
        _data = data;
        _enemyActive = config.getNight() > 3 ? 1 : 0;

        _aggression = 0.5f;
        _speed = 0.7f;
        setupNightParameters();
    }

    bool move(bool doorStatus) override
    {
        if(_enemyActive)
        {
            if(_moveCooldawn > getMoveCooldawn() + rand() % 1000)
            {
                _moveCooldawn = 0;
                if(_data->enemyPosition[_ID] == 10)
                {
                    _data->enemyPosition[_ID] = 0;
                    return doorStatus;
                }
                getMovePosition();
                useFake();
            }
            else
            {
                _moveCooldawn++;
            }
        }
        return 1; 
    }
};