#pragma once
#include <SDL.h>

#include "sdl_error.hpp"
#include "sdl_texture.hpp"

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

    sdl_texture create_texture( int width, int height )
    {
        const auto format = SDL_PIXELFORMAT_ARGB8888;
        const auto access = SDL_TEXTUREACCESS_STREAMING;
        auto texture = SDL_CreateTexture( _renderer, format, access,
                                          width, height );
        if ( texture == nullptr )
            sdl_error();

        return sdl_texture( texture );
    }

    void update( sdl_texture &texture, const void *pixels, int pitch )
    {
        texture.update( _renderer, pixels, pitch );
    }

    ~sdl_renderer()
    {
        if ( _renderer != nullptr )
            SDL_DestroyRenderer( _renderer );
    }

private:

    SDL_Renderer *_renderer;
};

