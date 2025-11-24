#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <array>
#include <fstream>
#include <cmath>

namespace GameConstant
{
    constexpr int WIDTH = 1024;
    constexpr int HEIGHT = 800;

    constexpr float ENERGY_CAPACITY = 3000.0;
    constexpr size_t BASED_NIGHT_TIME = 10000;

    constexpr size_t ENEMY_COUNT = 4;

    constexpr size_t SIZE_LABTOP = 10;
    constexpr size_t SHOCK_TIME_RELOAD = 300;

    constexpr size_t SIZE_OFFICE  = 3;
    constexpr float TIME_PAR = 0.05f;
    constexpr float PARALAX_INTENSITY = 0.3f;
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
    GameConfig(){ loadFromFile(); }
    ~GameConfig(){}

    GameConfig(GameConfig const&);
    GameConfig& operator= (GameConfig const&);

public:
    static GameConfig& Instance()
    {
        static GameConfig config;
        return config;
    }

    void saveToFile()
    {
        std::ofstream file("save.dat", std::ios::binary);
        if(file)
        {
            file.write(reinterpret_cast<const char*>(this), sizeof(GameConfig));
        }
    }
    void loadFromFile()
    {
        std::ifstream file("save.dat", std::ios::binary);
        if(file)
        {
            file.read(reinterpret_cast<char*>(this), sizeof(GameConfig));
        }
    }

    int getWidth(){ return _width; }
    int getHeight(){ return _height; }

    //void setWidth(size_t  width){ _width = width; }
    //void setHeight(size_t height){ _height = height; }

    void changeGameStatus(){ _gameStatus = !_gameStatus; }
    bool getGameStatus(){ return _gameStatus; }

    size_t getNight(){ return _night; }

private:
    std::array<size_t, SIZE_LABTOP> _cameraUsage = {0};
    std::array<size_t, 2> _doorUsage = {0};

    size_t _energyWaste = 0;
    size_t _death = 0;

    int _width = WIDTH;
    int _height = HEIGHT;

    bool _gameStatus = 1;
    size_t _night = 1;
};
static GameConfig& config = GameConfig::Instance();

extern SDL_Window* window;
extern SDL_Renderer* renderer;