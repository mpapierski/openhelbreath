#ifndef SURFACE_H
#define SURFACE_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Surface
{
public:
    Surface();

    static SDL_Surface *LoadFromImage(const std::string& FileName);

    static bool Draw(SDL_Surface *Dest, SDL_Surface *Src, int X, int Y);

    static bool Draw(SDL_Surface* Dest, SDL_Surface* Src, int X, int Y, int X2, int Y2, int W, int H);

    static bool SetTransparent(SDL_Surface *Surf_Dest, int R, int G, int B);
};

#endif // SURFACE_H
