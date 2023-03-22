#pragma once
#include <SDL.h>

#include "sdl_error.hpp"

struct sdl_renderer
{
    sdl_renderer( SDL_Window *window, int index, Uint32 flags )
        : _renderer( SDL_CreateRenderer( window, index, flags ) )
    {
        if ( _renderer == nullptr )
            sdl_error();
    }

    void clear()
    {
        SDL_RenderClear( _renderer );
    }

    void set_colour( int r, int g, int b, int a = SDL_ALPHA_OPAQUE )
    {
        if ( SDL_SetRenderDrawColor( _renderer, r, g, b, a ) < 0 )
            sdl_error();
    }

    void render()
    {
        SDL_RenderPresent( _renderer );
    }

    ~sdl_renderer()
    {
        SDL_DestroyRenderer( _renderer );
    }

private:

    SDL_Renderer *_renderer;
};

