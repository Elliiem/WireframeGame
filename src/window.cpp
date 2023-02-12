#include "window.h"
#include "inputs.h"
#include "globals.h"
#include "point.h"
#include <SDL2/SDL.h>
#include <fmt/format.h>
#include <iostream>
#include <chrono>
#include <vector>

Win::Win(int width, int height)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    win = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, height, width, 0);
    rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_BLEND);

    surface = SDL_GetWindowSurface(win);
}

void Win::DrawLine(int x1, int y1, int x2, int y2, Uint32* color)
{
    int x = 0;
    int y = 0;

    if(x1>x2)
    {
        std::swap(x1,x2);
        std::swap(y1,y2);
    }

    int dx = x2 - x1;
    int dy = y2 - y1;
    float ky = -((float)dy/(float)dx);
    float kx = 1/abs(ky);

    float ly = 0;
    float lx = 0;

    int neg = 1;

    if (ky<0)
        neg = -1;

    if(abs(ky) <= 1)
    {
        while (x<x2-x1)
        {
            SetPixel(x1+x,y1-y,color);
            ly += ky;
            if (abs(ly-y)<= 1)
                x++;
            else
            {
                y += neg;
                ly -= ky;
            }
        }
        SetPixel(x1+x,y1-y,color);
    }
    else if(abs(ky)>1)
    {
        while(abs(y)<=abs(y2-y1))
        {
            SetPixel(x1+x,y1-y,color);
            lx += kx;
            if(lx-x <= 0)
                y += neg;
            else
            {
                x++;
                lx -= kx;
            }
        }
        SetPixel(x2,y2,color);
    }
}

void Win::DrawRect(int x1, int y1, int x2, int y2, Uint32* color)
{
    int width = x2 - x1;
    int height = y2 - y1;
    for (int y=0;y<=height;y++)
    {
        std::memset((Uint32*)surface->pixels+GetIndex(x1,y1+y),*color,width*4);
    }

}

int Win::GetIndex(int x,int y)
{
    return (Uint32)(y*(surface->w)+x);
}

int Win::SetPixel(int x,int y, Uint32* color)
{
    if(x<0|x>=1919)
    {
        return 1;
    }
    else if(y<0|y>=1079)
    {
        return 1;
    }
     *((Uint32*)surface->pixels+GetIndex(x,y)) = *color;
    return 0;
}

void Win::GetPixelColor(int x, int y,SDL_Color* colorP)
{
    SDL_GetRGBA(*((Uint32*)surface->pixels+GetIndex(x,y)),surface->format,&colorP->r,&colorP->g,&colorP->b,&colorP->a);
}

void Win::CheckEvents()
{

    while (SDL_PollEvent(&event))
    {
        // Check for KeyEvents and Update keyboard
        INP_GetInputs(event, &keyboard);

        // Check for QUIT Event
        if (event.type == SDL_QUIT)
        {
            quit = true;
        }

        // Check for Quit Key-combination
        if (keyboard[SDLK_LCTRL] & keyboard[SDLK_z])
        {
            quit = true;
        }
    }
}

void Win::DrawPolygon(std::vector<Point> points, Uint32* color,int x,int y)
{
    int len = points.size();
    for(int i=0;i<len-1;i++)
    {
        DrawLine(points.at(i).x+x,points.at(i).y+y,points.at(i+1).x+x,points.at(i+1).y+y,color);
    }
    DrawLine(points.back().x+x,points.back().y+y,points.at(0).x+x,points.at(0).y+y,color);
}

void Win::Clear()
{
    int len = surface->pitch*1079;
    std::memset(surface->pixels,0,len);
}
