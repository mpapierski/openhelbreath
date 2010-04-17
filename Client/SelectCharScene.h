#ifndef SELECTCHARSCENE_H
#define SELECTCHARSCENE_H

#include "Scene.h"

#pragma pack(1)

typedef struct
{
		char Name[10];
		char _Unused;
		short Appr1, Appr2, Appr3, Appr4;
		short Gender, Skin;
		unsigned int Level, Experience;
		short Strength, Vitality, Dexterity, Intelligence,Magic, Agility;
		short Year, Month, Day, Hour, Minute, Second;
		char MapLoc[10];
} CCharacter;
typedef CCharacter CCharList[4];

#pragma pack(0)

class SelectCharScene: public Scene
{
	public:
		SelectCharScene(Buffer * P);
		~SelectCharScene();

		void Draw(SDL_Surface *Dest);

		void OnMouseMove(int X, int Y, int RelX, int RelY, bool Left, bool Right, bool Middle);

		void OnLButtonDown(int X, int Y);

		void OnKeyDown(SDLKey Sym, SDLMod Mod, Uint16 Unicode);

	private:
		enum Focus
		{
			Start, CreateNewChar, DelChar, ChangePasswd, Logout
		} ButtonFocus;

		int SlotSelect;
		int CharCount;
		CCharList CharList;
		void UpdateCharList(Buffer * B, int Skip = 0);
};

#endif // SELECTCHARSCENE_H
