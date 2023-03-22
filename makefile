
CXXFLAGS += -std=c++17 -pedantic -Wall -Wextra

all: mandelbrot

mandelbrot: main.cpp sdl2/*
	mkdir -p build
	${CXX} ${CFLAGS} -I/usr/include/SDL2 -lSDL2 -o build/$@ $<

