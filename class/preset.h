#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <array>
#include <cmath>

namespace GameConstant
{
    constexpr size_t WIDTH = 1024;
    constexpr size_t HEIGHT = 800;

    constexpr float ENERGY_CAPACITY = 3000.0;
    constexpr size_t BASED_NIGHT_TIME = 10000;

    constexpr size_t ENEMY_COUNT = 4;

    constexpr size_t SIZE_LABTOP = 10;
    constexpr size_t SHOCK_TIME_RELOAD = 300;

    constexpr size_t SIZE_OFFICE  = 3;
    constexpr float TIME_PAR = 0.05f;
    constexpr float PARALAX_INTENSITY = 0.04f;
};

enum class CameraName
{
    SCENE = 0,
    CAM_1 = 1,
    CAM_2 = 2,
    CAM_3 = 3,
    CAM_4 = 4,
    CAM_5 = 5,
    CAM_6 = 6,
    CAM_7 = 7,
    CAM_8 = 8,
    CAM_9 = 9
};

using namespace GameConstant;
class GameConfig
{
private:
    GameConfig(): _width(WIDTH), _height(HEIGHT){}
    ~GameConfig(){}

    GameConfig(GameConfig const&);
    GameConfig& operator= (GameConfig const&);

public:
    static GameConfig& Instance()
    {
        static GameConfig config;
        return config;
    }

    size_t getWidth(){ return _width; }
    size_t getHeight(){ return _height; }

    //void setWidth(size_t  width){ _width = width; }
    //void setHeight(size_t height){ _height = height; }

    void changeGameStatus(){ _gameStatus = !_gameStatus; }
    bool getGameStatus(){ return _gameStatus; }

    size_t getNight(){ return _night; }

private:
    size_t _width = 600;
    size_t _height = 300;

    bool _gameStatus = 1;
    size_t _night = 1;
};

static GameConfig& config = GameConfig::Instance();

extern SDL_Window* window;
extern SDL_Renderer* renderer;

//static const SDL_Rect full_viewport = {-width, 0, 3 * width, height};

//static size_t fps = 0;

//static bool attencion = 1;