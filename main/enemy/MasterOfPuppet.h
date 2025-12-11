#include "../struct/enemy.h"

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