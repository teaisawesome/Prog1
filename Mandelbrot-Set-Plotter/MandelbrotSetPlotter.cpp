// Forrás: https://github.com/SullyChen/Mandelbrot-Set-Plotter


#include "SFML/Graphics.hpp"

//resolution of the window
const int width = 1280;
const int height = 720;

//used for complex numbers
struct complex_number
{
    long double real;
    long double imaginary;
};

//mandelbrot komplex alapján legenerál egy mandelbrot halmazt
void generate_mandelbrot_set(sf::VertexArray& vertexarray, int pixel_shift_x, int pixel_shift_y, int precision, float zoom)
{
    #pragma omp parallel for
    for(int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //scale the pixel location to the complex plane for calculations
            long double x = ((long double)j - pixel_shift_x) / zoom;
            long double y = ((long double)i - pixel_shift_y) / zoom;
            complex_number c;
            c.real = x;
            c.imaginary = y;
            complex_number z = c;
            int iterations = 0; //keep track of the number of iterations
            for (int k = 0; k < precision; k++)
            {
                complex_number z2;
                z2.real = z.real * z.real - z.imaginary * z.imaginary;
                z2.imaginary = 2 * z.real * z.imaginary;
                z2.real += c.real;
                z2.imaginary += c.imaginary;
                z = z2;
                iterations++;
                if (z.real * z.real + z.imaginary * z.imaginary > 4)
                    break;
            }
            //color pixel based on the number of iterations
            if (iterations < precision / 4.0f)
            {
                vertexarray[i*width + j].position = sf::Vector2f(j, i);
                sf::Color color(iterations * 255.0f / (precision / 4.0f), 0, 0);
                vertexarray[i*width + j].color = color;
            }
            else if (iterations < precision / 2.0f)
            {
                vertexarray[i*width + j].position = sf::Vector2f(j, i);
                sf::Color color(0, iterations * 255.0f / (precision / 2.0f), 0);
                vertexarray[i*width + j].color = color;
            }
            else if (iterations < precision)
            {
                vertexarray[i*width + j].position = sf::Vector2f(j, i);
                sf::Color color(0, 0, iterations * 255.0f / precision);
                vertexarray[i*width + j].color = color;
            }
        }
    }
}

int main()
{
    sf::String title_string = "Mandelbrot Set Plotter"; //ablak címe
    sf::RenderWindow window(sf::VideoMode(width, height), title_string); //ablak objektum(létrehozza az ablakot a megadott méretekkel és címmel)
    window.setFramerateLimit(30); //frissített ablak/s vagy ilyesmi
    sf::VertexArray pointmap(sf::Points, width * height);
    

    //értékek inicializálása
    float zoom = 300.0f;
    int precision = 100;
    int x_shift = width / 2;
    int y_shift = height / 2;
    
    //legenerálja a mbh-t
    generate_mandelbrot_set(pointmap, x_shift, y_shift, precision, zoom);
    
    
    /**
     * 
     * 
     * 
     * 
     * */
    while (window.isOpen())
    {

        //ciklikusan figyeli az előforduló különböző event-eket, ha egy olyan esemény következik be, hogy rákattolunk az X gombra, akkor bezárja az ablakot
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        //ha a bal egérgommbal kattintunk, akkor az egér helyére nagyít az alábbi algoritmus segítségével. Minden nagyítás után újra legenerálja a mbh-t.
        //zoom into area that is left clicked
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i position = sf::Mouse::getPosition(window);
            x_shift -= position.x - x_shift;
            y_shift -= position.y - y_shift;
            zoom *= 2;
            precision += 200;
            
            #pragma omp parallel for
            for (int i = 0; i < width*height; i++)
            {
                pointmap[i].color = sf::Color::Black;
            }
            generate_mandelbrot_set(pointmap, x_shift, y_shift, precision, zoom);
        }
        window.clear();
        window.draw(pointmap);
        window.display();
    }
    
    return 0;
}
