#pragma once
#include <SDL.h>

#include "sdl_error.hpp"

struct sdl_context
{
    static sdl_context &get_context()
    {
        static sdl_context _context;
        return _context;
    }

    sdl_context( const sdl_context & ) = delete;
    sdl_context &operator =( const sdl_context & ) = delete;

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

private:
    sdl_context()
    {
        if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
            sdl_error();
    }
};
