#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <vector>

#include <SDL.h>

#include "Surface.h"
#include "Timer.h"

struct FrameSize
{
		short x;
		short y;
		short w;
		short h;
		short xOffset;
		short yOffset;
};

class Sprite
{
	public:
		Sprite();
		~Sprite();
		void update();
		void setFrameRect(short x, short y, short w, short h, short xOffset, short yOffset);
		FrameSize getFrameRect(int number) const;
		void setFramesCount(int frames);
		int getFramesCount() const;
		void setCurrentFrame(int frameID);
		int getCurrentFrame() const;
		void setMaxFrameH(int height);
		int getMaxFrameH() const;
		void setColorKey();
		void setColor(int r, int g, int b);

		inline SDL_Surface* getSurface() const
		{
			return image;
		}

		void setSurface(SDL_Surface* source)
		{
			this->image = SDL_ConvertSurface(source, source->format, source->flags);
			SDL_FreeSurface(source);
		}

	private:
		SDL_Surface* image;
		std::vector<FrameSize> framesRects;
		Timer frameTimer;
		int framesCount;
		int currentFrame;
		int maxFrameH;
};

#endif // SPRITE_H
