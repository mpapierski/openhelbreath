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
		void setMaxFrameW(int width);
		int getMaxFrameW() const;
		void setColorKey();

		inline SDL_Surface* getSurface() const
		{
			return image;
		}

		inline void setSurface(SDL_Surface* source)
		{
			this->image = SDL_ConvertSurface(source, source->format, source->flags);
			SDL_FreeSurface(source);
		}

		inline void releaseSurface()
		{
			SDL_FreeSurface(image);
			image = NULL;
		}

	private:
		SDL_Surface* image;
		std::vector<FrameSize> framesRects;
		Timer frameTimer;
		int framesCount;
		int currentFrame;
		int maxFrameH;
		int maxFrameW;
};

#endif // SPRITE_H
