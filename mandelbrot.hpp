#pragma once

#include <array>
#include <cassert>
#include <complex>
#include <string_view>
#include <tuple>
#include <vector>

#include "sdl2/sdl_renderer.hpp"
#include "sdl2/sdl_texture.hpp"

template< typename float_t = double >
struct mandelbrot
{
    using colour_t = std::tuple< int, int, int >;

    constexpr static float_t ratio = float_t( 2 ) / float_t( 3 );
    constexpr static int max_iterations = 64;
    constexpr static std::array< colour_t, 16 > colours{ {
        {  66,  30,  15 },
        {  25,   7,  26 },
        {   9,   1,  47 },
        {   4,   4,  73 },
        {   0,   7, 100 },
        {  12,  44, 138 },
        {  24,  82, 177 },
        {  57, 125, 209 },
        { 134, 181, 229 },
        { 211, 236, 248 },
        { 241, 233, 191 },
        { 248, 201,  95 },
        { 255, 170,   0 },
        { 204, 128,   0 },
        { 153,  87,   0 },
        { 106,  52,   3 },
    } };

    struct window;

    int _width;
    int _height;
    window _window;

    sdl_renderer &_renderer;
    sdl_texture _texture;

    std::vector< uint32_t > _data;

    mandelbrot( sdl_renderer &renderer, int width, int height,
                float_t start_x = -2, float_t start_y = -1,
                float_t window_width = 3, float_t window_height = 2 )
        : _width( width ),
          _height( height ),
          _window( start_x, start_y, window_width, window_height ),
          _renderer( renderer ),
          _texture( _renderer.create_texture( _width, _height ) ),
          _data( _width * _height, 0 )
    {}

    struct window
    {
        float_t pos_x;
        float_t pos_y;
        float_t width;
        float_t height;

        window( float_t x, float_t y, float_t w, float_t h )
            : pos_x( x ), pos_y( y ), width( w ), height( h )
        {}

        float_t real_x( float_t x, float_t window_width )
        {
            return width * x / window_width + pos_x;
        }

        float_t real_y( float_t y, float_t window_height )
        {
            return height * y / window_height + pos_y;
        }
    };

    void _zoom( int x, int y, float_t ratio )
    {
        const auto real_x = _window.real_x( x, _width );
        const auto real_y = _window.real_y( y, _height );

        _window.width *= ratio;
        _window.height *= ratio;

        _window.pos_x = real_x - _window.width / 2;
        _window.pos_y = real_y - _window.height / 2;
    }

    void zoom_in( int x, int y )
    {
        _zoom( x, y, ratio );
        update();
    }

    void zoom_out( int x, int y )
    {
        _zoom( x, y, float_t( 1 ) / ratio );
        update();
    }

    void resize( int width, int height )
    {
        if ( width == 0 || height == 0 )
            return;

        _window.width *= float_t( width ) / _width;
        _window.height *= float_t( height ) / _height;

        _width = width;
        _height = height;

        update();
    }

    void update()
    {
        const auto new_size = _width * _height;
        if ( _data.size() != new_size )
        {
            _data.resize( new_size, 0 );
            _texture = _renderer.create_texture( _width, _height );
        }

        compute_values();
    }

    void compute_values()
    {
        const float_t start_x = _window.real_x( 0, _width );
        const float_t start_y = _window.real_y( 0, _height );

        const float_t end_x = _window.real_x( _width, _width );
        const float_t end_y = _window.real_y( _height, _height );

        const float_t step_x = ( end_x - start_x ) / _width;
        const float_t step_y = ( end_y - start_y ) / _height;

        float_t px, py;
        int x, y;
        for ( x = 0, px = start_x; x < _width; ++x, px += step_x )
            for ( y = 0, py = start_y; y < _height; ++y, py += step_y )
                compute_pixel( { px, py }, x, y );

        _renderer.update( _texture, _data.data(), _width * sizeof( uint32_t ) );
    }

    void compute_pixel( std::complex< float_t > c, int x, int y )
    {
        std::complex< float_t > z( 0.0, 0.0 );

        int n = 0;
        while ( std::abs( z ) < 2.0 && n < max_iterations )
        {
            z = ( z * z ) + c;
            ++n;
        }

        if ( n == max_iterations )
            set_colour( x, y, { 0, 0, 0 } );
        else
            set_colour( x, y, colours[ n % 16 ] );
    }

    void set_colour( int x, int y, colour_t rgb )
    {
        auto [ r, g, b ] = rgb;
        _data[ y * _width + x ] = 0xFF << 24 | r << 16 | g << 8 | b;
    }

    void save( std::string_view filename )
    {
        update();

        auto s = _renderer.create_surface( _data.data(), _width, _height );
        s.save_image( filename );
    }
};

