#pragma once
#include <SDL.h>

#include <utility>

struct sdl_surface
{
    sdl_surface( SDL_Surface *surface )
        : _surface( surface )
    {}

    sdl_surface( const sdl_surface & ) = delete;
    sdl_surface &operator =( const sdl_surface & ) = delete;

    sdl_surface( sdl_surface &&o ) noexcept
        : _surface( std::exchange( o._surface, nullptr ) )
    {}

    sdl_surface &operator =( sdl_surface &&o ) noexcept
    {
        std::swap( _surface, o._surface );
        return *this;
    }

    void save_image( std::string_view filename )
    {
        IMG_SavePNG( _surface, filename.data() );
    }

    ~sdl_surface()
    {
        if ( _surface != nullptr )
            SDL_FreeSurface( _surface );
    }

private:

    SDL_Surface *_surface;
};
