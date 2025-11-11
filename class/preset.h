#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <array>
#include <cmath>
#include "classes.h"

//Всякие буквы - пресеты
static SDL_Window* window;
static SDL_Renderer* renderer;

static int width = 1020;
static int height = 800;
//static const SDL_Rect full_viewport = {-width, 0, 3 * width, height};

static bool gameStatus = 1;
static size_t night = 1;

static size_t fps = 0;

static bool attencion = 1;