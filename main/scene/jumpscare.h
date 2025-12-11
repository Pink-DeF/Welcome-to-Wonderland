#pragma once

#include "../based/classes.h"
#include "../struct/scene.h"

class JumpscareScene: public Scene
{
public:
    JumpscareScene(size_t ID);
    
    void draw() override;

private:
    size_t _enemyID = 10;
    size_t timer = 100;

    SDL_FRect rend {0, 0, static_cast<float>(config.getWidth()), static_cast<float>(config.getHeight())};

    std::map<size_t, SDL_Color> _frames
    {
        {SPRINGTIME_ID, SDL_Color {100, 200, 100, 255}},
        {ERRORTIME_ID,  SDL_Color {150, 150, 0, 255}},
        {MASTEROFPUPPET_ID, SDL_Color {100, 100, 100, 255}},
        {FOXDEN_ID, SDL_Color {255, 0, 100, 255}}
    };
};