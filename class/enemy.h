#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <array>
#include <cmath>

#define SIZE_ENEMY 10;

class FoxDen : public Enemy
{
public:
    FoxDen()
    {
        _position = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    }
    size_t move() override {}

private:
};

class MasterOfPuppet : public Enemy
{
public:
    MasterOfPuppet()
    {
        _position = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    }
    size_t move() override {}

private:

};

class SpringTime : public Enemy
{
public:
    SpringTime()
    {
        _position = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    }
    size_t move() override {}

private:

};

class ErrorTime : public Enemy
{
public:
    ErrorTime()
    {
        _position = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    }
    size_t move() override {}

private:

};