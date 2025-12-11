#include "../labtop.h"

LabtopScene::LabtopScene(std::array<SDL_Color, SIZE_LABTOP> tmp, std::shared_ptr<nightDB> data): _data(data){}
LabtopScene::LabtopScene(){}

void LabtopScene::draw()
{
    _shockTimer -= _shockTimer ? 1 : 0;
    _rechargShock = _shockTimer ? 1 : 0;
    if(_visible)
    {
        SDL_SetRenderViewport(renderer, NULL);
        _cams[_cam].draw();
        for(size_t i = 0; i < ENEMY_COUNT; i++)
        {
            if(_data->enemyPosition[i] == _cam)
            {
                _enemyTexture[i].draw();
            }
        }
        if(_data->MasterFakePosition == _cam)
        {
            _enemyTexture[MASTEROFPUPPET_ID].draw();
        }

        _data->energy -= 1;
    }
    return;
}

void LabtopScene::switchCamera(size_t num){ _cam = num < SIZE_LABTOP ? num : _cam; }
void LabtopScene::useShock()
{
    if(_cam == 6 && _rechargShock == 0)
    {
        if(_data->enemyPosition[0] == _cam) { _data->enemyPosition[0] = 0; }
        _rechargShock = 1;
        _shockTimer = SHOCK_TIME_RELOAD;
    }
}