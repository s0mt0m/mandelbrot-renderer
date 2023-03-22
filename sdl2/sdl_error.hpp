#pragma once
#include <SDL.h>

#include <iostream>

void sdl_error()
{
    std::cerr << "SDL error: " << SDL_GetError();
    exit( EXIT_FAILURE );
};

