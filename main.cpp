#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <string_view>

#include "mandelbrot.hpp"
#include "sdl2/sdl_context.hpp"
#include "sdl2/sdl_window.hpp"


static int error( std::string_view msg )
{
    std::cerr << msg << std::endl;
    return EXIT_FAILURE;
}

int main( int argc, char **argv )
{
    bool interactive = false;
    bool change_output = false;
    std::string_view filename = "mandelbrot.png";

    for ( int i = 1; i < argc; ++i )
    {
        std::string_view arg = argv[ i ];

        if ( arg == "-i" || arg == "--interactive" )
            interactive = true;
        else if ( arg == "-o" || arg == "--output" )
        {
            if ( argv[ ++i ] == nullptr )
                return error( "Missing output value" );

            filename = argv[ i ];
            change_output = true;
        }
        else
            return error( "Invalid option" );
    }

    if ( interactive && change_output )
        return error( "Options 'interactive' and 'output'"
                      " are mutually exclusive" );

    constexpr std::string_view title( "Mandelbrot set visualizer" );
    constexpr int width = 1280;
    constexpr int height = 720;

    sdl_context &context = sdl_context::get_context();
    sdl_window window = context.create_window( title, width, height );
    sdl_renderer renderer = window.create_renderer();

    mandelbrot mb( renderer, width, height );

    renderer.set_colour( 0, 0, 0 );
    renderer.clear();
    renderer.render();

    if ( !interactive )
    {
        mb.save( filename );
        return EXIT_SUCCESS;
    }

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
                if ( event.window.event == SDL_WINDOWEVENT_RESIZED )
                    mb.resize( event.window.data1, event.window.data2 );
            }
        }

        renderer.render();

        context.delay( 1000 / 30 );
    }
}

