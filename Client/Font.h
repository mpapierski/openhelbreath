#ifndef FONT_H
#define FONT_H

#include <SDL_ttf.h>
#include <string>

class Font
{
public:
	Font();
	~Font();

	Font(const std::string &FileName, int Size);

	static SDL_Surface *Draw(Font &SrcFont, const std::string &Text);

	SDL_Color GetColor() const;

	TTF_Font *GetFont() const;

	void LoadFont(const std::string &FileName, int Size);

	void SetColor(int R, int G, int B);

private:
	TTF_Font *FontHandle;

	SDL_Color Color;
};

#endif // FONT_H
