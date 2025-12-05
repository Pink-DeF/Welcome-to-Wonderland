#pragma once
#include "memory"

#include "preset.h"
#include "classes.h"

using namespace GameConstant;
class LabtopScene: public Scene
{
private:
    class CameraScene : public Scene
    {
    public:
        //Конструктор
        CameraScene(){}
        CameraScene(SDL_Color tmp, std::shared_ptr<nightDB> data): _data(data)
        {
            _object = object { SDL_FRect { 0, 0, static_cast<float>(config.getWidth()), static_cast<float>(config.getHeight())}, tmp};
            _viewport = {0, 0, 2 * config.getWidth(), config.getHeight()};
        }
 
        void move(bool direct)
        {
            if(direct && config.getWidth() <= config.getWidth() / 2){ _viewport.x += config.getWidth() * 0.05; }
            else if(!direct && config.getWidth() >= 0){ _viewport.x -= config.getWidth() * 0.05; }
        }

        //Ппросто отрисовка
        void draw() override
        { 
            SDL_SetRenderViewport(renderer, &_viewport);
            SDL_SetRenderDrawColor(renderer, _object.color.r, _object.color.g, _object.color.b, _object.color.a);
            SDL_RenderFillRect(renderer, &(_object.position));
            return;
        }

    private:
        std::shared_ptr<nightDB> _data;

        SDL_Rect _viewport;
        object _object;
    };

public:
    LabtopScene(std::array<SDL_Color, SIZE_LABTOP> tmp, std::shared_ptr<nightDB> data): _data(data)
    {
        for(size_t i = 0; i < SIZE_LABTOP; i++)
        {
            _cams[i] = CameraScene(tmp[i], data);
        }
    }
    LabtopScene(){}

    void draw() override
    {
        _shockTimer -= _shockTimer ? 1 : 0;
        _rechargShock = _shockTimer ? 1 : 0;
        if(_visible)
        {
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

    void switchCamera(size_t num){ _cam = num < SIZE_LABTOP ? num : _cam; }
    void useShock()
    {
        if(_cam == 6 && _rechargShock == 0)
        {
            if(_data->enemyPosition[0] == _cam) { _data->enemyPosition[0] = 0; }
            _rechargShock = 1;
            _shockTimer = SHOCK_TIME_RELOAD;
        }
    }
private:
    bool _rechargShock = 0;
    size_t _shockTimer = 0;

    std::array<Texture, ENEMY_COUNT> _enemyTexture =
    {
        Texture{IMG_LoadTexture(renderer, "Texture/legenda.jpg"), SDL_FRect{600, 100, 300, 600}, SDL_FRect{180, 150, 350, 700}},
        Texture{IMG_LoadTexture(renderer, "Texture/doomguy.jpg"), SDL_FRect{100, 100, 300, 600}, SDL_FRect{800, 0, 1250, 2400}},
        Texture{IMG_LoadTexture(renderer, "Texture/Senko.png"), SDL_FRect{150, 200, 500, 500}, SDL_FRect{0, 0, 1447, 2039}},
        Texture{IMG_LoadTexture(renderer, "Texture/master.jpg"), SDL_FRect{400, 100, 600, 610}, SDL_FRect{40, 130, 1400, 1450}}
    };

    std::shared_ptr<nightDB> _data;
    std::array<CameraScene, SIZE_LABTOP> _cams;
    size_t _cam = 0;
};