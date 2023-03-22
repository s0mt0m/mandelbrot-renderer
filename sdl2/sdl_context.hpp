#pragma once
#include <SDL.h>

#include "sdl_error.hpp"

struct sdl_context
{
    sdl_context()
    {
        if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
            sdl_error();
    }

    bool should_quit() const
    {
        return SDL_QuitRequested();
    }

    void delay( int ms )
    {
        SDL_Delay( ms );
    }

    ~sdl_context()
    {
        SDL_Quit();
    }
};

