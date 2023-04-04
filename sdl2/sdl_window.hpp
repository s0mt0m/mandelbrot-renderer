#pragma once
#include <SDL.h>

#include "sdl_error.hpp"
#include "sdl_renderer.hpp"

struct sdl_window
{
    sdl_window( SDL_Window *window )
        : _window( window )
    {}

    sdl_window( const sdl_window & ) = delete;
    sdl_window &operator =( const sdl_window & ) = delete;

    sdl_window( sdl_window &&o ) noexcept
        : _window( std::exchange( o._window, nullptr ) )
    {}

    sdl_window &operator =( sdl_window &&o ) noexcept
    {
        std::swap( _window, o._window );
        return *this;
    }

    sdl_renderer create_renderer( int index = -1, Uint32 flags = 0 )
    {
        auto renderer = SDL_CreateRenderer( _window, index, flags );
        if ( renderer == nullptr )
            sdl_error();

        return sdl_renderer( renderer );
    }

    ~sdl_window()
    {
        if ( _window != nullptr )
            SDL_DestroyWindow( _window );
    }

private:

    SDL_Window *_window;
};

