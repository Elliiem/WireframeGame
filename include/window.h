#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <vector>
#include "inputs.h"
#include "point.h"

class Win
{
    public:
    SDL_Window* win;
    SDL_Renderer* rend;
    SDL_Event event;
    SDL_Surface* surface;
    Win(int width, int height);
    void DrawLine(int x1, int y1, int x2, int y2, Uint32* color);
    void DrawRect(int x1,int y1, int x2,int y2, Uint32* color);
    void DrawPoint(int x, int y, SDL_Color* color);
    int GetIndex(int x, int y);
    int SetPixel(int x, int y, Uint32* color);
    void GetPixelColor(int x, int y, SDL_Color* colorP);
    void CheckEvents();
    void DrawPolygon(std::vector<Point>, Uint32* color,int x,int y);
    void Clear();
};
# endif
