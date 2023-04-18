# mandelbrot-renderer

A simple multi-threaded interactive renderer of Mandelbrot set based on SDL library.

![Mandelbrot set](mandelbrot.png)

## Requirements

* make
* SDL
* SDL_image

## Usage

Compile the sources

`$ make`

Run the code

`$ ./mandelbrot -i`

Available options:

* `-i`, `--interactive` - Runs the program in an interactive mode.
Clicking the left mouse button zooms in, clicking the right button zooms out.
If this options is not specified, the program just saves the rendered image.

* `-o FILENAME`, `--output FILENAME` - If `--interactive` is not specified,
change the name of saved image (default `mandelbrot.png`)
