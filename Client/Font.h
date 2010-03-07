#ifndef FONT_H
#define FONT_H

#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

class CFont
{
public:
    CFont();

    bool OnLoad(const std::string &FileName, int Size);

    void SetColor(int R, int G, int B);

    SDL_Surface *OnRender(const std::string &Text);

    void OnCleanup();

private:
    TTF_Font *Font;

    SDL_Color TextColor;
};

#endif // FONT_H
