#pragma once
#include <memory>

#include "../based/init.h"
#include "../based/classes.h"
#include "../struct/scene.h"

using namespace GameConstant;
class OfficeScene : public Scene
{
private:
    class _Door
    {
    private:
        void animate();

    public:
        _Door();
        _Door(std::shared_ptr<nightDB> data, size_t ID, float height, Texture textureD, Texture hall);

        bool getStatus();
        bool getFlashStatus();

        void draw();

        void changeDoorStatus(size_t target);

        float useEnergy();

    private:
        std::shared_ptr<nightDB> _data;
        Texture _hall = {};
        Texture _textureDoor = {};
        size_t _ID = 0;

        size_t _height = 0;

        bool inAnimation = 0;
        float _timePar = 0;

        bool _closeStatus = 0;
        bool _closeAnimStatus = 0;
        bool _flashStatus = 0;
    };

    void move();
    
    void calculateEnergy();
    void useParalax();

public:
    //Конструктор
    OfficeScene(){}
    OfficeScene(std::shared_ptr<nightDB> data): _data(data)
    { _viewport = _posViewport = {-config.getWidth(), 0, 3 * config.getWidth(), config.getHeight()}; }

    //Ппросто отрисовка
    void draw() override;

    //Geters
    bool getLeftDoorStatus();
    bool getRightDoorStatus();

    bool getLeftDoorFlash();
    bool getRightDoorFlash();

    int getCameraPosition();
    bool noMove();

    //chengers
    void changeDoorStatus(size_t target);

    void changeCameraPosition(bool direct);
    void mouseMotion(SDL_MouseMotionEvent& motion);

private:
    std::shared_ptr<nightDB> _data;

    Texture _office = Texture{IMG_LoadTexture(renderer, "Texture/office.jpg"),
            SDL_FRect{0, 0, static_cast<float>(config.getWidth())* 3, static_cast<float>(config.getHeight())},
            SDL_FRect{0, 0, 3072, 800}};

    _Door _leftDoor = _Door(_data, 11, static_cast<float>(config.getHeight()) * 5 / 10,
            Texture{IMG_LoadTexture(renderer, "Texture/leftDoor.jpg"),
            SDL_FRect{0, static_cast<float>(config.getHeight()) / 10, static_cast<float>(config.getWidth()) * 2 / 5, 0},
            SDL_FRect{50, 0, 800, 900}},
            Texture{IMG_LoadTexture(renderer, "Texture/leftFlash.png"),
            SDL_FRect{0, static_cast<float>(config.getHeight()) / 10, static_cast<float>(config.getWidth()) * 2 / 5, static_cast<float>(config.getHeight()) * 4 / 10},
            SDL_FRect{0, 0, 960, 934}});
    _Door _rightDoor = _Door(_data, 10, static_cast<float>(config.getHeight()) * 9 / 10,
            Texture{IMG_LoadTexture(renderer, "Texture/rightDoor.jpg"),
            SDL_FRect{static_cast<float>(config.getWidth()) * 13 / 5, static_cast<float>(config.getHeight()) / 10, static_cast<float>(config.getWidth()) * 2 / 5, 0},
            SDL_FRect{0, 0, 700, 1400}},
            Texture{IMG_LoadTexture(renderer, "Texture/rightFlash.jpg"),
            SDL_FRect{static_cast<float>(config.getWidth()) * 13 / 5, static_cast<float>(config.getHeight()) * 2 / 10, static_cast<float>(config.getWidth()) * 2 / 5, static_cast<float>(config.getHeight()) * 6 / 10},
            SDL_FRect{0, 0, 960, 934}});

    paralax _paralax;
    SDL_Rect _posViewport;
    SDL_Rect _viewport; 

    bool _invertControl = 0;

    float _timePar = 0;
    int _cameraPosition = 0; 
    int _cameraTargetPosition = 0;
};