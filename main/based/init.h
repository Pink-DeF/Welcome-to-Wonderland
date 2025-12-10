#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

#include "global.h"

extern SDL_Window* window;
extern SDL_Renderer* renderer;

static GameConfig& config = GameConfig::Instance();