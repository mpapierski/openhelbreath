#ifndef FONT_H
#define FONT_H

#include <SDL_ttf.h>
#include <string>

SDL_Surface *DrawText(TTF_Font *Font, const std::string &Text, int R, int G, int B);

#endif // FONT_H
