#include "night.h"

void Night::setRechargEnergy()
{
    if(_data->energy <= 0){ _data->rechargEnergy = 1; }
    else if(_data->energy >= ENERGY_CAPACITY){ _data->rechargEnergy = 0; }

    if(_data->rechargEnergy)
    {
        if(labtop.itVisible())
        {
            office.changeVisible();
            labtop.changeVisible();
        }
        
        office.changeDoorStatus(0);
    }
}
void Night::draw()
{
    SDL_RenderClear(renderer);
    office.draw();
    labtop.draw();
    _monitorTime += labtop.itVisible();
}
size_t  Night::enemyMove()
{
    if(!_springTime.move(office.getRightDoorStatus())){ _live = 0; return SPRINGTIME_ID; }
    else if(!_errorTime.move(office.getLeftDoorFlash())){ _live = 0; return ERRORTIME_ID; }
    else if(!_foxDen.move(office.getLeftDoorStatus())){ _live = 0; return FOXDEN_ID; }
    else if(!_master.move(office.getRightDoorStatus())){ _live = 0; return MASTEROFPUPPET_ID; }
    return 100;
}

Night::Night(): _data(std::make_shared<nightDB>())
{
    office = OfficeScene {_data};//Сцена Офиса и его компонентов 

    labtop = LabtopScene //Сцена планшета и камер
    {
        std::array<SDL_Color, SIZE_LABTOP>
            {
                SDL_Color {218, 131, 225, 255},
                SDL_Color {70, 83, 15, 255},
                SDL_Color {177, 29, 22, 255},
                SDL_Color {126, 65, 101, 255},
                SDL_Color {2, 70, 189, 255},
                SDL_Color {67, 34, 116, 255},
                SDL_Color {180, 20, 3, 255},
                SDL_Color {27, 45, 80, 255},
                SDL_Color {187, 179, 230, 255},
                SDL_Color {203, 73, 176, 255}
            }, _data
    };

    office.changeVisible();
}

SDL_AppResult Night::iterate()
{
    _nightTime--;

    setRechargEnergy();
    _jumpscare = enemyMove();

    draw();
    if(_nightTime == 0 ) { config.win(); }
    else if(_live == 0)
    {
        screamer = { _jumpscare };
        screamer.draw();
        config.lose();
    }
    return SDL_APP_CONTINUE;
}

void Night::gameEvent(SDL_KeyboardEvent& key)
{
    if(key.key == SDLK_S && !office.getCameraPosition() && !_data->rechargEnergy)
    {
        office.changeVisible();
        labtop.changeVisible();
    }
    else if(labtop.itVisible() && (key.key >= SDLK_0 && key.key <= SDLK_9))
    {
        labtop.switchCamera(key.key - SDLK_0);
    }
    else if(labtop.itVisible() && key.key == SDLK_F){ labtop.useShock(); }
    else if(office.itVisible())
    {
        if(key.key == SDLK_A){ office.changeCameraPosition(0); }
        else if(key.key == SDLK_D){ office.changeCameraPosition(1); }
        else if(!_data->rechargEnergy && key.key == SDLK_S){ office.changeDoorStatus(1); }
        else if(!_data->rechargEnergy && key.key == SDLK_F){ office.changeDoorStatus(2); }
    }
}
void Night::mouseEvent(SDL_MouseMotionEvent& motion)
{
    if(office.itVisible())
    {
        office.mouseMotion(motion);
    }
}