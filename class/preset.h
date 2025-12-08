#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <array>
#include <fstream>

namespace GameConstant
{
    constexpr int WIDTH = 1024;
    constexpr int HEIGHT = 800;

    constexpr float ENERGY_CAPACITY = 2000.0;
    constexpr size_t BASED_NIGHT_TIME = 200000;

    constexpr size_t ENEMY_COUNT = 4;

    constexpr size_t SIZE_LABTOP = 10;
    constexpr size_t SHOCK_TIME_RELOAD = 300;

    constexpr float TIME_PAR = 0.05f;
    constexpr float PARALAX_INTENSITY = 0.05f;

    constexpr size_t SPRINGTIME_ID = 0;
    constexpr size_t ERRORTIME_ID = 1;
    constexpr size_t MASTEROFPUPPET_ID = 2;
    constexpr size_t FOXDEN_ID = 3;
};

extern SDL_Window* window;
extern SDL_Renderer* renderer;

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

        _gameStatus = 0;
    }

    int getWidth(){ return _width; }
    int getHeight(){ return _height; }

    void newGame(){ _night = 1; doStart(); }
    void changeGameStatus(){ _gameStatus = !_gameStatus; }
    void doStart(){ _startGame = 1; }
    bool getGameStatus(){ return _gameStatus; }
    bool start()
    {
        if(_startGame)
        {
            _gameStatus = 1;
            _startGame = 0;
            return 1;
        }
        return 0;
    }

    size_t getNight(){ return _night; }
    void lose() { _gameStatus = 0; }
    void win()
    {
        _gameStatus = 0;
        _night++;
        saveToFile();
    }

private:
    int _width = WIDTH;
    int _height = HEIGHT;

    bool _gameStatus = 0;
    bool _startGame = 0;
    size_t _night = 0;
};

static GameConfig& config = GameConfig::Instance();