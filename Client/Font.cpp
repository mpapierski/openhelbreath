//
// Font container and common font routines
//

#include "Font.h"
#include "SpriteBank.h"

TTF_Font* Font::smallFont;
TTF_Font* Font::normalFont;

SDL_Surface* Font::text(const std::string& text, FontSize size, int r, int g, int b)
{
	if (text.empty())
		return NULL;

	SDL_Surface* returnSurface = NULL;

	SDL_Color color;
	color.r = r;
	color.g = g;
	color.b = b;

	switch (size)
	{
		case SMALL:
			returnSurface = TTF_RenderUTF8_Solid(smallFont, text.c_str(), color);
			break;
		case NORMAL:
			returnSurface = TTF_RenderUTF8_Solid(normalFont, text.c_str(), color);
			break;
		case LARGE:
			break;
	}

	return returnSurface;

}

SDL_Surface* Font::textShaded(const std::string& text, FontSize size, int r, int g, int b)
{
	if (text.empty())
		return NULL;

	SDL_Surface* shadowSurface = NULL;
	SDL_Surface* textSurface = NULL;

	SDL_Color shadowColor = { 0, 0, 0 };
	SDL_Color textColor = { r, g, b };

	switch (size)
	{
		case SMALL:
			shadowSurface = TTF_RenderUTF8_Solid(smallFont, text.c_str(), shadowColor);
			break;
		case NORMAL:
			shadowSurface = TTF_RenderUTF8_Solid(normalFont, text.c_str(), shadowColor);
			break;
		case LARGE:
			break;
	}

	SDL_Surface* temp = Surface::createSurface(shadowSurface->w, shadowSurface->h, 128, 128, 128,
			255);

	Surface::setColorKey(temp, 128, 128, 128);

	Surface::draw(temp, shadowSurface, 0, 0);

	switch (size)
	{
		case SMALL:
			textSurface = TTF_RenderUTF8_Solid(smallFont, text.c_str(), textColor);
			break;
		case NORMAL:
			textSurface = TTF_RenderUTF8_Solid(normalFont, text.c_str(), textColor);
			break;
		case LARGE:
			break;
		}

	Surface::draw(temp, textSurface, -1, -1);

	SDL_FreeSurface(shadowSurface);
	SDL_FreeSurface(textSurface);

	return temp;
}

static char Space[] = { 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 6, 8, 7, 8, 8, 9, 10, 9, 7,
		8, 8, 8, 8, 8, 8, 8, 15, 16, 12, 17, 14, 15, 14, 16, 10, 13, 19, 10, 17, 17, 15, 14, 15,
		16, 13, 17, 16, 16, 20, 17, 16, 14, 8, 8, 8, 8, 8, 8, 8, 6, 7, 8, 7, 7, 7, 7, 4, 7, 7, 4,
		11, 7, 8, 8, 7, 8, 6, 5, 8, 9, 14, 8, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8 };

SDL_Surface* Font::sprText(const std::string& text)
{
	if (text.empty())
		return NULL;

	int Pos = 0;
	int Width = 0;

	for (unsigned int i = 0; i < text.size(); i++)
	{
		int Number = static_cast<char> (text.at(i));
		if ((Number >= 33) && (Number <= 122))
		{
			Width += Space[Number - 33];
		}
		else
			Width += 5;
	}

	SDL_Surface* returnSurface = NULL;

	returnSurface = Surface::createSurface(Width,
			SpriteBank::manager.getSprite(SPRID_SPRFONT).getMaxFrameH(), 128, 128, 128, 255);

	if (returnSurface == NULL)
	{
		return NULL;
	}

	for (unsigned int i = 0; i < text.size(); i++)
	{
		int Number = static_cast<char> (text.at(i));
		if ((Number >= 33) && (Number <= 122))
		{

			SpriteBank::manager.draw(returnSurface, Pos, 0, SPRID_SPRFONT, (Number - 33));
			Pos += Space[Number - 33];
		}
		else
			Pos += 5;
	}

	Surface::setColorKey(returnSurface, 128, 128, 128);

	return returnSurface;
}

int Font::textWidth(const std::string& text, FontSize size)
{
	if (text.empty())
		return 0;

	int w;
	switch (size)
	{
		case SMALL:
			TTF_SizeUTF8(smallFont, text.c_str(), &w, NULL);
			break;
		case NORMAL:
			TTF_SizeUTF8(normalFont, text.c_str(), &w, NULL);
			break;
		case LARGE:
			break;
	}

	return w;
}

int Font::textHeight(const std::string& text, FontSize size)
{
	if (text.empty())
		return 0;

	int h;
	switch (size)
	{
		case SMALL:
			TTF_SizeUTF8(smallFont, text.c_str(), NULL, &h);
			break;
		case NORMAL:
			TTF_SizeUTF8(normalFont, text.c_str(), NULL, &h);
			break;
		case LARGE:
			break;
	}

	return h;
}

void Font::putText(SDL_Surface* dest, int x, int y, const std::string& text, FontSize size, int r, int g, int b)
{
	SDL_Surface* txt = Font::text(text, size, r, g, b);
	Surface::draw(dest, txt, x, y);
	SDL_FreeSurface(txt);
}

void Font::putTextShaded(SDL_Surface* dest, int x, int y, const std::string& text, FontSize size, int r, int g, int b)
{
	SDL_Surface* txt = Font::textShaded(text, size, r, g, b);
	Surface::draw(dest, txt, x, y);
	SDL_FreeSurface(txt);
}

void Font::putAlignedText(SDL_Surface* dest, int x, int y, int width, const std::string& text, FontSize size, int r, int g, int b)
{
	Font::putText(dest, (x + (width / 2) - (Font::textWidth(text, size) / 2)), y, text, size, r, g, b);
}

void Font::putSprText(SDL_Surface* dest, int x, int y, const std::string& text)
{
	SDL_Surface* txt = Font::sprText(text);
	Surface::draw(dest, txt, x, y);
	SDL_FreeSurface(txt);
}

void Font::putAlignedSprText(SDL_Surface* dest, int x, int y, int width, const std::string& text)
{
	SDL_Surface* txt = Font::sprText(text);
	if (txt != NULL)
		Surface::draw(dest, txt, (x + (width / 2) - (txt->w / 2)), y);

	SDL_FreeSurface(txt);
}

void Font::putTextSprF(SDL_Surface* dest, int x, int y, const std::string& text)
{
	char __cSpace2[] = { 6, 4, 6, 6, 6, 6, 6, 6, 6, 6, 6 };
	unsigned int iCnt;
	int xpos = 0;
	int W = 0;

	for (iCnt = 0; iCnt < text.length(); iCnt++)
	{
		char tmp = text.at(iCnt);
		if ((tmp >= '0') && (tmp <= '9'))
			tmp = tmp - '0' + 6;
		else if (tmp == '!')
			tmp = 17;
		else if (tmp == '.')
			tmp = 18;
		else if (tmp == 'V')
			tmp = 19;
		else
			continue;
		W += tmp < (int) sizeof(__cSpace2) ? __cSpace2[(int) tmp] : (tmp == 19 ? 19 + 3 : 6);
	}

	SDL_Surface* output = Surface::createSurface(W, 10, 27, 88, 153, 200);
	for (iCnt = 0; iCnt < text.length(); iCnt++)
	{
		char tmp = text.at(iCnt);
		if ((tmp >= '0') && (tmp <= '9'))
			tmp = tmp - '0' + 6;
		else if (tmp == '!')
			tmp = 17;
		else if (tmp == '.')
			tmp = 18;
		else if (tmp == 'V')
			tmp = 19;
		else
			continue;
		SpriteBank::manager.draw(output, xpos, 0, SPRID_INTERFACE2, tmp);
		xpos += tmp < (int) sizeof(__cSpace2) ? __cSpace2[(int) tmp] : (tmp == 19 ? 19 + 3 : 6);
	}
	Surface::replaceColor(output, SDL_MapRGB(output->format, 0, 0, 0), SDL_MapRGB(output->format,
			255, 255, 255));
	Surface::setColorKey(output, 27, 88, 153);
	Surface::draw(dest, output, x, y);
	SDL_FreeSurface(output);
}
