#pragma once
#include <SDL.h>

#include "sdl_error.hpp"
#include "sdl_window.hpp"

struct sdl_context
{
    static sdl_context &get_context()
    {
        static sdl_context _context;
        return _context;
    }

    sdl_context( const sdl_context & ) = delete;
    sdl_context &operator =( const sdl_context & ) = delete;

    sdl_window create_window( std::string_view title, int width, int height )
    {
        const auto pos_undef = SDL_WINDOWPOS_UNDEFINED;
        const auto flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
        auto window = SDL_CreateWindow( title.data(), pos_undef, pos_undef,
                                        width, height, flags );
        if ( window == nullptr )
            sdl_error();

        return sdl_window( window );
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

private:
    sdl_context()
    {
        if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
            sdl_error();
    }
};
