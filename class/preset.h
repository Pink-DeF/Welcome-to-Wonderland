#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <array>
#include <cmath>
//#include "classes.h"

/*
class Singleton
{
  public:
    static Singleton& Instance()
    {
        // согласно стандарту, этот код ленивый и потокобезопасный
        static Singleton s;
        return s;
    }

  private:
    Singleton() {}  // конструктор недоступен
    ~Singleton() {} // и деструктор

    // необходимо также запретить копирование
    Singleton(Singleton const&); // реализация не нужна
    Singleton& operator= (Singleton const&);  // и тут
};
*/

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

    SDL_Window* getWindow(){ return _window; }
    SDL_Renderer*getRenderer() { return _renderer; }

    int getWidth(){ return _width; }
    int getHeight(){ return _height; }

    void changeGameStatus(){ _gameStatus = !_gameStatus; }
    bool getGameStatus(){ return _gameStatus; }

    size_t getNight(){ return _night; }

private:
    SDL_Window* _window;
    SDL_Renderer* _renderer;

    int _width = 1020;
    int _height = 800;

    bool _gameStatus = 1;
    size_t _night = 1;
};

GameConfig& config = GameConfig::Instance();

static SDL_Window* window;
static SDL_Renderer* renderer;

//static int width = 1020;
//static int height = 800;
//static const SDL_Rect full_viewport = {-width, 0, 3 * width, height};

//static size_t fps = 0;

//static bool attencion = 1;