#include "../struct/enemy.h"

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