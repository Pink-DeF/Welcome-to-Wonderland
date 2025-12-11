#pragma once
#include "../based/init.h"
#include "../based/classes.h"

#include "../struct/scene.h"
#include "../struct/button.h"

class MainMenuScene : public Scene
{
private:
    void draw() override;

public:
    MainMenuScene();
    SDL_AppResult iterate();

    SDL_AppResult click(SDL_MouseButtonEvent& button);

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