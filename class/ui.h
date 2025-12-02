#pragma once
#include "preset.h"

class MainMenuScene : public Scene
{
private:
    class _Button
    {
    public:
        _Button() {}
        _Button(object obj): _obj(obj) {}

        void draw(){ _obj.draw(); }
        bool touch(float x, float y)
        {
            return _obj.position.x < x && (_obj.position.w + _obj.position.x) > x &&
                _obj.position.y < y && (_obj.position.h + _obj.position.y) > y ? 1 : 0;
        }

    protected:
        object _obj = {};
    };

    void draw() override
    {
        SDL_SetRenderViewport(renderer, NULL);
        _wallpap.draw();
        
        for(auto i: _buttons)
        {
            i.draw();
        }
    }

public:
    MainMenuScene()
    {
        _buttons[0]= _Button({{static_cast<float>(config.getWidth()) / 30, static_cast<float>(config.getHeight()) / 5, static_cast<float>(config.getWidth()) / 3, static_cast<float>(config.getHeight()) / 6}, {200, 200, 200, 255}});
        _buttons[1] = _Button({{static_cast<float>(config.getWidth()) / 30, static_cast<float>(config.getHeight()) * 2 / 5, static_cast<float>(config.getWidth()) / 3, static_cast<float>(config.getHeight()) / 6}, {200, 200, 200, 255}});
        _buttons[2]= _Button({{static_cast<float>(config.getWidth()) / 30, static_cast<float>(config.getHeight()) * 3 / 5, static_cast<float>(config.getWidth()) / 3, static_cast<float>(config.getHeight()) / 6}, {200, 200, 200, 255}});
    }
    SDL_AppResult iterate()
    {
        draw();

        return SDL_APP_CONTINUE;
    }

    SDL_AppResult click(SDL_MouseButtonEvent& button)
    {
        if(_buttons[0].touch(button.x, button.y)){ config.newGame(); }
        if(_buttons[1].touch(button.x, button.y)){ config.doStart(); }
        else if(_buttons[2].touch(button.x, button.y)){ return SDL_APP_SUCCESS; }

        return SDL_APP_CONTINUE;
    }

private:
    object _wallpap = {{0, 0, static_cast<float>(config.getWidth()), static_cast<float>(config.getHeight())}, {100, 100, 100, 255}};

    std::array<_Button, 3> _buttons;
};