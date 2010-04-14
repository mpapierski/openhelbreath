#include "Font.h"
#include "Game.h"

SDL_Surface *Font::Text(const std::string &Text, int R, int G, int B)
{
	if (Text.empty())
		return NULL;

	SDL_Surface *ReturnSurface = NULL;

	SDL_Color Color;
	Color.r = R;
	Color.g = G;
	Color.b = B;
	ReturnSurface = TTF_RenderUTF8_Solid(Game::GetInstance().Font,
			Text.c_str(), Color);

	return ReturnSurface;
}

SDL_Surface *Font::TextShaded(const std::string &Text, int R, int G, int B)
{
	if (Text.empty())
	{
		return NULL;
	}

	SDL_Surface *ShadowSurface = NULL;
	SDL_Surface *TextSurface = NULL;

	SDL_Color ShadowColor =
	{ 0, 0, 0 };

	SDL_Color TextColor;
	TextColor.r = R;
	TextColor.g = G;
	TextColor.b = B;

	ShadowSurface = TTF_RenderUTF8_Solid(Game::GetInstance().Font,
			Text.c_str(), ShadowColor);

	SDL_Surface *Temp = Surface::CreateSurface(ShadowSurface->w,
			ShadowSurface->h, 128, 128, 128, 255);

	Surface::SetTransparent(Temp, 128, 128, 128);

	Surface::Draw(Temp, ShadowSurface, 0, 0);

	TextSurface = TTF_RenderUTF8_Solid(Game::GetInstance().Font, Text.c_str(),
			TextColor);

	Surface::Draw(Temp, TextSurface, -1, -1);

	SDL_FreeSurface(ShadowSurface);
	SDL_FreeSurface(TextSurface);

	return Temp;
}

static char Space[] =
{
		8,
		8,
		8,
		8,
		8,
		8,
		8,
		8,
		8,
		8,
		8,
		8,
		8,
		8,
		8,
		8,
		6,
		8,
		7,
		8,
		8,
		9,
		10,
		9,
		7,
		8,
		8,
		8,
		8,
		8,
		8,
		8,
		15,
		16,
		12,
		17,
		14,
		15,
		14,
		16,
		10,
		13,
		19,
		10,
		17,
		17,
		15,
		14,
		15,
		16,
		13,
		17,
		16,
		16,
		20,
		17,
		16,
		14,
		8,
		8,
		8,
		8,
		8,
		8,
		8,
		6,
		7,
		8,
		7,
		7,
		7,
		7,
		4,
		7,
		7,
		4,
		11,
		7,
		8,
		8,
		7,
		8,
		6,
		5,
		8,
		9,
		14,
		8,
		9,
		8,
		8,
		8,
		8,
		8,
		8,
		8,
		8,
		8,
		8,
		8,
		8 };

SDL_Surface *Font::SprText(const std::string &Text)
{
	if (Text.empty())
	{
		return NULL;
	}

	int Pos = 0;
	int Width = 0;

	for (unsigned int i = 0; i < Text.size(); i++)
	{
		int Number = static_cast<char> (Text.at(i));
		if ((Number >= 33) && (Number <= 122))
		{
			Width += Space[Number - 33];
		}
		else
			Width += 5;
	}

	SDL_Surface *ReturnSurface = NULL;

	ReturnSurface = Surface::CreateSurface(Width,
			Game::GetInstance().Sprites[SPRID_SPRFONT].GetMaxFrameH(), 128,
			128, 128, 255);

	if (ReturnSurface == NULL)
	{
		return NULL;
	}

	for (unsigned int i = 0; i < Text.size(); i++)
	{
		int Number = static_cast<char> (Text.at(i));
		if ((Number >= 33) && (Number <= 122))
		{
			Sprite::Draw(ReturnSurface,
					Game::GetInstance().Sprites[SPRID_SPRFONT], Pos, 0, (Number
							- 33));
			Pos += Space[Number - 33];
		}
		else
			Pos += 5;
	}

	Surface::SetTransparent(ReturnSurface, 128, 128, 128);

	return ReturnSurface;
}

int Font::TextWidth(const std::string &Text)
{
	int W, H;
	TTF_SizeText(Game::GetInstance().Font, Text.c_str(), &W, &H);
	return W;
}

int Font::TextHeight(const std::string &Text)
{
	int W, H;
	TTF_SizeUTF8(Game::GetInstance().Font, Text.c_str(), &W, &H);
	return H;
}

void Font::PutText(SDL_Surface *Dest, int X, int Y, const std::string &Text,
		int R, int G, int B)
{
	SDL_Surface * _txt = Font::Text(Text, R, G, B);
	Surface::Draw(Dest, _txt, X, Y);
	SDL_FreeSurface(_txt);
}

void Font::PutTextShaded(SDL_Surface *Dest, int X, int Y,
		const std::string &Text, int R, int G, int B)
{
	SDL_Surface * _txt = Font::TextShaded(Text, R, G, B);
	Surface::Draw(Dest, _txt, X, Y);
	SDL_FreeSurface(_txt);
}

void Font::PutAlignedText(SDL_Surface *Dest, int X, int Y, int Width,
		const std::string & Text, int R, int G, int B)
{
	Font::PutText(Dest, X + ((Width - Font::TextWidth(Text)) / 2), Y, Text, R,
			G, B);
}

void Font::PutSprText(SDL_Surface *Dest, int X, int Y, const std::string &Text)
{
	SDL_Surface * _txt = Font::SprText(Text);
	Surface::Draw(Dest, _txt, X, Y);
	SDL_FreeSurface(_txt);
}

void Font::PutAlignedSprText(SDL_Surface *Dest, int X, int Y, int Width,
		const std::string & Text)
{
	SDL_Surface * _txt = Font::SprText(Text);
	Surface::Draw(Dest, _txt, X + ((Width - _txt->w) / 2), Y);
	SDL_FreeSurface(_txt);
}

void Font::PutTextSprF(SDL_Surface * Dest, int X, int Y,
		const std::string & Text)
{
	char __cSpace2[] =
	{ 6, 4, 6, 6, 6, 6, 6, 6, 6, 6, 6 };
	unsigned int iCnt;
	int xpos = 0;
	int W = 0;

	for (iCnt = 0; iCnt < Text.length(); iCnt++)
	{
		char tmp = Text.at(iCnt);
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

	SDL_Surface * Output = Surface::CreateSurface(W, 10, 27, 88, 153, 200);
	for (iCnt = 0; iCnt < Text.length(); iCnt++)
	{
		char tmp = Text.at(iCnt);
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
		Sprite::Draw(Output, Game::GetInstance().Sprites[SPRID_SPRFONT_NUM],
				xpos, 0, tmp);
		xpos += tmp < (int) sizeof(__cSpace2) ? __cSpace2[(int) tmp] : (tmp == 19 ? 19 + 3 : 6);
	}
	Surface::ReplaceColor(Output, SDL_MapRGB(Output->format, 0, 0, 0),
			SDL_MapRGB(Output->format, 140, 140, 140));
	Surface::SetTransparent(Output, 27, 88, 153);
	Surface::Draw(Dest, Output, X, Y);
	SDL_FreeSurface(Output);
}

