#pragma once
#include <SDL.h>

#include <utility>

#include "sdl_error.hpp"

struct sdl_texture
{
    sdl_texture( SDL_Texture *texture )
        : _texture( texture )
    {}

    sdl_texture( const sdl_texture & ) = delete;
    sdl_texture &operator =( const sdl_texture & ) = delete;

    sdl_texture( sdl_texture &&o ) noexcept
        : _texture( std::exchange( o._texture, nullptr ) )
    {}

    sdl_texture &operator =( sdl_texture &&o ) noexcept
    {
        std::swap( _texture, o._texture );
        return *this;
    }

    void update( SDL_Renderer *renderer, const void *pixels, int pitch )
    {
        if ( SDL_UpdateTexture( _texture, nullptr, pixels, pitch ) < 0 )
            sdl_error();

        if ( SDL_RenderCopy( renderer, _texture, nullptr, nullptr ) < 0 )
            sdl_error();
    }

    ~sdl_texture()
    {
        if ( _texture != nullptr )
            SDL_DestroyTexture( _texture );
    }

private:

    SDL_Texture *_texture;
};

