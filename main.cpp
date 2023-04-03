#include <SDL.h>

#include <iostream>
#include <string_view>

#include "mandelbrot.hpp"
#include "sdl2/sdl_context.hpp"
#include "sdl2/sdl_window.hpp"


int main()
{
    constexpr std::string_view title( "Mandelbrot set visualizer" );
    constexpr int width = 1280;
    constexpr int height = 720;

    sdl_context &context = sdl_context::get_context();
    sdl_window window = context.create_window( title, width, height );
    sdl_renderer renderer = window.create_renderer();

    mandelbrot mb( renderer, width, height );

    SDL_Event event;
    while ( !context.should_quit() )
    {
        while ( SDL_PollEvent( &event ) )
        {
            if ( event.type == SDL_MOUSEBUTTONDOWN )
            {
                if ( event.button.button == SDL_BUTTON_LEFT )
                    mb.zoom_in( event.motion.x, event.motion.y );
                else if ( event.button.button == SDL_BUTTON_RIGHT)
                    mb.zoom_out( event.motion.x, event.motion.y );
            }
            else if ( event.type == SDL_WINDOWEVENT )
            {
                if ( event.window.event == SDL_WINDOWEVENT_EXPOSED )
                    mb.resize( event.window.data1, event.window.data2 );
            }
        }

        renderer.render();

        context.delay( 1000 / 30 );
    }
}

