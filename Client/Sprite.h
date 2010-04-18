#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>
#include <string>
#include <vector>

#include "Surface.h"
#include "GlobalDef.h"

struct Cord
{
		short X;
		short Y;
		short W;
		short H;
		short Vx;
		short Vy;
};

class Sprite
{
	public:
#ifdef DEF_CACHE
		int Priority;
		int ID;
		bool Locked;
		std::string Name;
		static std::vector<Sprite*> Cache;
		static void ReleaseUnused();
#endif
		Sprite();
		~Sprite();
		Sprite(const std::string & FileName, int Number);
		bool Init(const std::string & FileName, int Number);
		inline bool LoadFromFile(const std::string & FileName, int Number);
		static bool Draw(SDL_Surface *Dest, Sprite & SpriteSrc, int X, int Y, int Frame);
		static bool Draw(SDL_Surface *Dest, Sprite & SpriteSrc, int X, int Y, int W, int H, int Frame);
		SDL_Surface *GetSurface() const;
		Cord GetCord(int Number) const;
		int GetTotalFrames() const;
		int GetMaxFrameH() const;
		void SetColorKey();

		inline bool getTransparent() const
		{
			return Transparent;
		}

		void setTransparent(bool Transparent)
		{
			this->Transparent = Transparent;
		}

		SDL_Surface *getImage() const
		{
			return Image;
		}

		void setImage(SDL_Surface *Image)
		{
			this->Image = Image;
		}

	private:
		SDL_Surface *Image;
		std::vector<Cord> Cords;
		int TotalFrames;
		int MaxFrameH;
		bool Transparent;
};

#endif // SPRITE_H
