#pragma once
#include <SDL.h>

#include "sdl_error.hpp"

struct sdl_renderer
{
    sdl_renderer( SDL_Renderer *renderer )
        : _renderer( renderer )
    {}

    sdl_renderer( const sdl_renderer & ) = delete;
    sdl_renderer &operator =( const sdl_renderer & ) = delete;

    sdl_renderer( sdl_renderer &&o ) noexcept
        : _renderer( std::exchange( o._renderer, nullptr ) )
    {}

    sdl_renderer &operator =( sdl_renderer &&o ) noexcept
    {
        std::swap( _renderer, o._renderer );
        return *this;
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

