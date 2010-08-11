#include "Sprite.h"

static FrameSize emptyFrameRect = { 0, 0, 0, 0, 0, 0 };

Sprite::Sprite()
{
	image = NULL;
        currentFrame = 0;
}

void Sprite::update()
{
    if (!frameTimer.isStarted()) frameTimer.start();

    if (frameTimer.getTicks() > 100)
    {
        currentFrame++;
        if (currentFrame >= framesCount) currentFrame = 0;

        frameTimer.start();
    }
}

void Sprite::setFrameRect(short x, short y, short w, short h, short xOffset, short yOffset)
{
	FrameSize tempFrameRect = { x, y, w, h, xOffset, yOffset };
	framesRects.push_back(tempFrameRect);
}

FrameSize Sprite::getFrameRect(int number) const
{
	if ((framesRects.size() - 1) < static_cast<unsigned int> (number))
	{
		return emptyFrameRect;
	}
	else
		return framesRects.at(number);
}

void Sprite::setFramesCount(int frames)
{
	framesCount = frames;
}

int Sprite::getFramesCount() const
{
	return framesCount;
}

void Sprite::setCurrentFrame(int frameID)
{
	currentFrame = frameID;
}

int Sprite::getCurrentFrame() const
{
	return currentFrame;
}

void Sprite::setMaxFrameH(int height)
{
	maxFrameH = height;
}

int Sprite::getMaxFrameH() const
{
	return maxFrameH;
}

void Sprite::setColorKey()
{
	if (image == NULL)
		return;

	SDL_PixelFormat* fmt;
	Uint32 temp, pixel;
	Uint8 index, alpha;
	SDL_Color color;

	color.r = 0;
	color.g = 0;
	color.b = 0;

	fmt = image->format;

	SDL_LockSurface(image);

	if (fmt->BitsPerPixel == 32)
	{
		/* Get the topleft pixel */
		pixel = *((Uint32*) image->pixels);

		/* Get Red component */
		temp = pixel & fmt->Rmask; /* Isolate red component */
		temp = temp >> fmt->Rshift; /* Shift it down to 8-bit */
		temp = temp << fmt->Rloss; /* Expand to a full 8-bit number */
		color.r = static_cast<Uint8>(temp);

		/* Get Green component */
		temp = pixel & fmt->Gmask; /* Isolate green component */
		temp = temp >> fmt->Gshift; /* Shift it down to 8-bit */
		temp = temp << fmt->Gloss; /* Expand to a full 8-bit number */
		color.g = (Uint8) temp;

		/* Get Blue component */
		temp = pixel & fmt->Bmask; /* Isolate blue component */
		temp = temp >> fmt->Bshift; /* Shift it down to 8-bit */
		temp = temp << fmt->Bloss; /* Expand to a full 8-bit number */
		color.b = (Uint8) temp;

		/* Get Alpha component */
		temp = pixel & fmt->Amask; /* Isolate alpha component */
		temp = temp >> fmt->Ashift; /* Shift it down to 8-bit */
		temp = temp << fmt->Aloss; /* Expand to a full 8-bit number */
		alpha = (Uint8) temp;
	}

	if (fmt->BitsPerPixel == 8)
	{
		/* Get the topleft pixel */
		index = *(Uint8 *)image->pixels;
		color = fmt->palette->colors[index];
	}

	/* Unlock the surface */
	SDL_UnlockSurface(image);

	SDL_SetColorKey(image, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(
							image->format, color.r, color.g, color.b));
}

void Sprite::setColor(int r, int g, int b)
{

}

Sprite::~Sprite()
{

}
