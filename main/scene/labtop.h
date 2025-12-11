#pragma once
#include "memory"

#include "../based/init.h"
#include "../based/classes.h"
#include "../struct/scene.h"

using namespace GameConstant;
class LabtopScene: public Scene
{
public:
    LabtopScene(std::array<SDL_Color, SIZE_LABTOP> tmp, std::shared_ptr<nightDB> data);
    LabtopScene();

    void draw() override;

    void switchCamera(size_t num);
    void useShock();

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
    size_t _cam = 0;
    std::array<Texture, SIZE_LABTOP> _cams =
    {
        Texture{IMG_LoadTexture(renderer, "Texture/camera/null.png"),
                SDL_FRect{0, 0, static_cast<float>(config.getWidth()), static_cast<float>(config.getHeight())},
                SDL_FRect{0, 0, 1024, 800}},
        Texture{IMG_LoadTexture(renderer, "Texture/camera/first.png"),
                SDL_FRect{0, 0, static_cast<float>(config.getWidth()), static_cast<float>(config.getHeight())},
                SDL_FRect{0, 0, 1024, 800}},
        Texture{IMG_LoadTexture(renderer, "Texture/camera/second.png"),
                SDL_FRect{0, 0, static_cast<float>(config.getWidth()), static_cast<float>(config.getHeight())},
                SDL_FRect{0, 0, 1024, 800}},
        Texture{IMG_LoadTexture(renderer, "Texture/camera/third.png"),
                SDL_FRect{0, 0, static_cast<float>(config.getWidth()), static_cast<float>(config.getHeight())},
                SDL_FRect{0, 0, 1024, 800}},
        Texture{IMG_LoadTexture(renderer, "Texture/camera/fourth.png"),
                SDL_FRect{0, 0, static_cast<float>(config.getWidth()), static_cast<float>(config.getHeight())},
                SDL_FRect{0, 0, 1024, 800}},
        Texture{IMG_LoadTexture(renderer, "Texture/camera/fifth.png"),
                SDL_FRect{0, 0, static_cast<float>(config.getWidth()), static_cast<float>(config.getHeight())},
                SDL_FRect{0, 0, 1024, 800}},
        Texture{IMG_LoadTexture(renderer, "Texture/camera/sixth.png"),
                SDL_FRect{0, 0, static_cast<float>(config.getWidth()), static_cast<float>(config.getHeight())},
                SDL_FRect{0, 0, 1024, 800}},
        Texture{IMG_LoadTexture(renderer, "Texture/camera/seventh.png"),
                SDL_FRect{0, 0, static_cast<float>(config.getWidth()), static_cast<float>(config.getHeight())},
                SDL_FRect{0, 0, 1024, 800}},
        Texture{IMG_LoadTexture(renderer, "Texture/camera/eight.png"),
                SDL_FRect{0, 0, static_cast<float>(config.getWidth()), static_cast<float>(config.getHeight())},
                SDL_FRect{0, 0, 1024, 800}},
        Texture{IMG_LoadTexture(renderer, "Texture/camera/ninth.png"),
                SDL_FRect{0, 0, static_cast<float>(config.getWidth()), static_cast<float>(config.getHeight())},
                SDL_FRect{0, 0, 1024, 800}},
    };
};