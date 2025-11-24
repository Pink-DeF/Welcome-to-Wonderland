#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <array>
#include <cmath>

#include "class/night.h"
//#include "class/ui.h"

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

Night game(1);
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
    if(!SDL_Init(SDL_INIT_VIDEO)) return SDL_APP_FAILURE;

    SDL_CreateWindowAndRenderer("Welcome to Wonderland", config.getWidth(), config.getHeight(), 0, &window, &renderer);
    //game = Night(config.getNight());

    srand(time(nullptr));

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate)
{
    SDL_RenderPresent(renderer);
    SDL_Delay(15);

    return game.iterate();
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    switch (event->type)
    {
        case SDL_EVENT_QUIT:
            return SDL_APP_SUCCESS;
        case SDL_EVENT_KEY_DOWN:
            game.gameEvent(event->key);
            break;
        case SDL_EVENT_MOUSE_MOTION:
            game.mouseEvent(event->motion);
            break;
    }
    return SDL_APP_CONTINUE;
}
void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    config.saveToFile();
}
