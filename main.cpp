#include <SDL.h>

#include <iostream>

#include "sdl2/sdl_context.hpp"
#include "sdl2/sdl_window.hpp"


int main()
{
    sdl_context context;

    sdl_window window( "test", 720, 540 );
    sdl_renderer renderer = window.create_renderer();

    while ( !context.should_quit() )
    {
        renderer.set_colour( 0, 0, 0 );
        renderer.clear();

        renderer.render();

        context.delay( 1000 / 30 );
    }
}

