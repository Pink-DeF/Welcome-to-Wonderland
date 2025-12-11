#include "../FoxDen.h"

void FoxDen::getMovePosition()
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

FoxDen::FoxDen(std::shared_ptr<nightDB> data, size_t ID)
{
    _ID = ID;
    _data = data;
    _enemyActive = config.getNight() > 1 ? 1 : 0;

    _aggression = 0.5f;
    _speed = 0.7f;
    setupNightParameters();
}


void FoxDen::doubleJump()
{
    if((_data->enemyPosition[_ID] != 10 && _data->enemyPosition[_ID] != 11) && rand() % 1 <= 0.2f)
    {
        getMovePosition();
    }
}

bool FoxDen::move(bool doorStatus)
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