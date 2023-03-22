#pragma once
#include <SDL.h>

#include "sdl_error.hpp"
#include "sdl_renderer.hpp"

struct sdl_window
{
    sdl_window( const char *name, int width, int height,
            int flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE,
            int pos_x = SDL_WINDOWPOS_UNDEFINED,
            int pos_y = SDL_WINDOWPOS_UNDEFINED )
        : _window( SDL_CreateWindow( name, pos_x, pos_y,
                                     width, height, flags ) )
    {
        if ( _window == nullptr )
            sdl_error();
    }

    sdl_renderer create_renderer( int index = -1, Uint32 flags = 0 )
    {
        return sdl_renderer( _window, index, flags );
    }

    ~sdl_window()
    {
        SDL_DestroyWindow( _window );
    }

private:

    SDL_Window *_window;
};

