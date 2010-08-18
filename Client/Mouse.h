#ifndef MOUSE_H
#define MOUSE_H

#include "Event.h"
#include "SpriteBank.h"

class Mouse : public Event
{
	public:
		enum Style
		{
			ARROW,
			LIFT_ITEM_1,
			LIFT_ITEM_2,
			ATTACK,
			TARGET_SPELL_NEUTRAL,
			TARGET_SPELL_ENEMY,
			ARROW_NEUTRAL,
			ARROW_ENEMY,
			THINK,
			TARGET_1,
			TARGET_2,
			TARGET_3,
			BLACK
		};

		Mouse();
		~Mouse();
		void onDraw(SDL_Surface* dest);
		void onEvent(SDL_Event* eventSource);
		void onMouseMove(int x, int y, int relX, int relY, bool left, bool right, bool middle);
		void setCursorStyle(Style cStyle);

	private:
		int cursorX;
		int cursorY;
		Style cursorStyle;
};

#endif // MOUSE_H
