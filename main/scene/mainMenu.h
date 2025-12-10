#pragma once
#include "../based/init.h"
#include "../based/classes.h"

class MainMenuScene : public Scene
{
private:
    void draw() override
    {
        SDL_SetRenderViewport(renderer, NULL);
        // _wallpap.draw();

        for (auto i: _buttons){ i.draw(); }
    }

public:
    MainMenuScene(){}
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
    Texture _wallpap;

    std::array<Button, 3> _buttons =
    {
        Texture{IMG_LoadTexture(renderer, "Texture/button/newgame.png"),
                SDL_FRect {static_cast<float>(config.getWidth()) / 30, static_cast<float>(config.getHeight()) / 5, static_cast<float>(config.getWidth()) * 2 / 5, static_cast<float>(config.getHeight()) / 6},
                SDL_FRect{0, 0, 860, 180}},
        Texture{IMG_LoadTexture(renderer, "Texture/button/continue.png"),
                SDL_FRect {static_cast<float>(config.getWidth()) / 30, static_cast<float>(config.getHeight()) * 2 / 5, static_cast<float>(config.getWidth()) * 2 / 5, static_cast<float>(config.getHeight()) / 6},
                SDL_FRect{0, 0, 860, 180}},
        Texture{IMG_LoadTexture(renderer, "Texture/button/quit.png"),
                SDL_FRect {static_cast<float>(config.getWidth()) / 30, static_cast<float>(config.getHeight()) * 3 / 5, static_cast<float>(config.getWidth()) * 2 / 5, static_cast<float>(config.getHeight()) / 6},
                SDL_FRect{0, 0, 860, 180}},
    };
};