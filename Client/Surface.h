#ifndef SURFACE_H
#define SURFACE_H

#include <string>

#include <SDL.h>
#include <SDL_image.h>

class CSurface
{
public:
    CSurface();

public:
    static SDL_Surface *LoadFromImage(const std::string &FileName);

    static bool OnDraw(SDL_Surface *Surf_Dest, SDL_Surface *Surf_Src, int X, int Y);

    static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y, int X2, int Y2, int W, int H);

    static bool Transparent(SDL_Surface *Surf_Dest, int R, int G, int B);
};

#endif // SURFACE_H
