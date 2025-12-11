#include "../ErrorTime.h"

void ErrorTime::getMovePosition()
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

ErrorTime::ErrorTime(std::shared_ptr<nightDB> data, size_t ID)
{
    _ID = ID;
    _data = data;
    _enemyActive = config.getNight() > 2 ? 1 : 0;

    _aggression = 0.1f;
    _speed = 0.5f;
    setupNightParameters();
}

void ErrorTime::joke()
{
    size_t random = static_cast<size_t>(rand() % 10000);
    switch(random)
    {
        case(1):
            _data->invertTime = 300;
            break;
    }
}

bool ErrorTime::move(bool doorStatus)
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