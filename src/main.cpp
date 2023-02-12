#include <SDL2/SDL.h>
#include <fmt/format.h>
#include <iostream>

#include <unistd.h>
#include <map>
#include <vector>
#include <chrono>

#include "inputs.h"
#include "window.h"
#include "globals.h"
#include "point.h"
#include "sprite.h"

int main()
{
    // Init
    // -----------------------------------------------
    // create window
    // Play Around
    std::vector<Point> Points = {Point(100,0),Point(-100,-70),Point(-50,0),Point(-100,70)};
    Sprite Spaceship(Points);
    int x = 500;
    int y = 500;
    Spaceship.Rotate(0);
    // -----------------------------------------------
    // Main-loop
    // -----------------------------------------------
    while (!quit)
    {
        auto start = std::chrono::steady_clock::now();
        // Handle Win Events
        // -----------------------------------------------
        Win.CheckEvents();
        // -----------------------------------------------

        // Draw Something
        // -----------------------------------------------
        SDL_UpdateWindowSurface(Win.win);
        Win.Clear();
        if(keyboard[SDLK_d])
        {
            Spaceship.Rotate(6);
        }
        if(keyboard[SDLK_a])
        {
            Spaceship.Rotate(-6);
        }
        if(keyboard[SDLK_w])
        {
            x += cos((Spaceship.rot)*0.017453292519943295)*40;
            y -= sin((Spaceship.rot)*0.017453292519943295)*40;
        }
        if(x <= 0)
        {
            x = 1920;
        }
        if(x > 1920)
        {
            x = 0;
        }
        if (y <= 0)
        {
            y = 1080;
        }
        if(y > 1080)
        {
            y = 0;
        }
        Spaceship.Draw(x,y);
        auto end = std::chrono::steady_clock::now();
        float time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        fmt::print("{}\n",time);
        // -----------------------------------------------
    }

    // -----------------------------------------------

    // Destroy
    // -----------------------------------------------
    SDL_DestroyRenderer(Win.rend);
    SDL_DestroyWindow(Win.win);
    SDL_Quit();
    // -----------------------------------------------

    return 0;
}
