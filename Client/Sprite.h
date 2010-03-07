#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <vector>

#include <SDL.h>

class CSprite
{
public:
    CSprite();
    ~CSprite();

    CSprite(const std::string &FileName, int Number);

    bool SetImage(const std::string &FileName, int Number);

    SDL_Surface *GetImage();

    std::vector<SDL_Rect>Frame;

private:
    SDL_Surface *Image;
};

#endif // SPRITE_H
