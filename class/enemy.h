#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <array>
#include <cmath>

class SpringTime : public Enemy
{
public:
    SpringTime()
    {
    }
    size_t move() override
    {
    }

private:

};

class ErrorTime : public Enemy
{
public:
    ErrorTime()
    {
    }
    size_t move() override {}

private:

};

class MasterOfPuppet : public Enemy
{
public:
    MasterOfPuppet()
    {
    }
    size_t move() override {}

private:

};

class FoxDen : public Enemy
{
public:
    FoxDen()
    {
    }
    size_t move() override {}

private:
};