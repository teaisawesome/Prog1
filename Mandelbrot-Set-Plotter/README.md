# Mandelbrot-Set-Plotter
A C++ and SFML program that let's you plot the approximate Mandelbrot Set and zoom in.

Includes for SFML:
    sudo apt-get update
    sudo apt-get install libsfml-dev

Build command:  
    g++ MandelbrotSetPlotter.cpp -lsfml-window -lsfml-system -lsfml-graphics  -fopenmp -O2
Run command:
    g++ -o mbhzoom MandelbrotSetPlotter.cpp -lsfml-window -lsfml-system -lsfml-graphics -fopenmp -O2
    ./mbhzoom
