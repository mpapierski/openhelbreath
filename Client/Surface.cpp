#include "Surface.h"

Surface::Surface()
{

}

SDL_Surface* Surface::loadFromImage(const std::string& fileName)
{
	SDL_Surface* temp = NULL;
	SDL_Surface* returnSurface = NULL;

	if((temp = IMG_Load(fileName.c_str())) == NULL)
	{
		printf("Unable to load: %s", fileName.c_str());
		return NULL;
	}

	returnSurface = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);

	return returnSurface;
}

SDL_Surface* Surface::createSurface(int w, int h, int r, int g, int b, int alpha)
{
	SDL_Surface* returnSurface = NULL;

	returnSurface = SDL_CreateRGBSurface(SDL_HWSURFACE, w, h, 32, 0, 0, 0, 0);

	if(returnSurface == NULL)
	{
		fprintf(stderr, "CreateRGBSurface failed: %s\n", SDL_GetError());
		exit(1);
	}

	SDL_FillRect(returnSurface, NULL, SDL_MapRGB(returnSurface->format, r, g, b));

	SDL_SetAlpha(returnSurface, SDL_SRCALPHA | SDL_RLEACCEL, alpha);

	return returnSurface;
}

bool Surface::draw(SDL_Surface* dest, SDL_Surface* src, int x, int y)
{
	if (dest == NULL || src == NULL)
	{
		return false;
	}

	SDL_Rect destR;

	destR.x = x;
	destR.y = y;

	SDL_BlitSurface(src, NULL, dest, &destR);

	return true;
}

bool Surface::draw(SDL_Surface* dest, SDL_Surface* src, int x, int y, int x2, int y2, int w, int h)
{
	if(dest == NULL || src == NULL)
	{
		return false;
	}

	SDL_Rect destR;

	destR.x = x;
	destR.y = y;

	SDL_Rect srcR;

	srcR.x = x2;
	srcR.y = y2;
	srcR.w = w;
	srcR.h = h;

	SDL_BlitSurface(src, &srcR, dest, &destR);

	return true;
}

bool Surface::setColorKey(SDL_Surface* dest, int r, int g, int b)
{
	if(dest == NULL)
	{
		return false;
	}

	SDL_SetColorKey(dest, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(dest->format, r, g, b));

	return true;
}

Uint32 Surface::getPixel32(SDL_Surface* src, int x, int y)
{
	//Convert the pixels to 32 bit
	Uint32* pixels = (Uint32 *)src->pixels;
	//Get the requested pixel
	return pixels[ ( y * src->w ) + x ];
}

void Surface::replaceColor(SDL_Surface* dest, Uint32 a, Uint32 b)
{
	int bpp = dest->format->BytesPerPixel;
	if (SDL_MUSTLOCK(dest))
		SDL_LockSurface(dest);
	for (int x = 0; x < dest->w; x++)
		for (int y = 0; y < dest->h; y++)
			if (*(Uint32 *) ((Uint8 *) dest->pixels + y * dest->pitch + x
					* bpp) == a)
				*(Uint32 *) ((Uint8 *) dest->pixels + y * dest->pitch + x
						* bpp) = b;
	if (SDL_MUSTLOCK(dest))
		SDL_UnlockSurface(dest);
}
