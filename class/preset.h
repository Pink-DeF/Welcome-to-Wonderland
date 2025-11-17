#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <array>
#include <cmath>

class GameConfig
{
private:
    GameConfig(){}
    ~GameConfig(){}

    GameConfig(GameConfig const&);
    GameConfig& operator= (GameConfig const&);

public:
    static GameConfig& Instance()
    {
        static GameConfig config;
        return config;
    }

    int getWidth(){ return _width; }
    int getHeight(){ return _height; }

    void changeGameStatus(){ _gameStatus = !_gameStatus; }
    bool getGameStatus(){ return _gameStatus; }

    size_t getNight(){ return _night; }

private:
    int _width = 1020;
    int _height = 800;

    bool _gameStatus = 1;
    size_t _night = 1;
};

static GameConfig& config = GameConfig::Instance();

static SDL_Window* window;
static SDL_Renderer* renderer;

//static const SDL_Rect full_viewport = {-width, 0, 3 * width, height};

//static size_t fps = 0;

//static bool attencion = 1;