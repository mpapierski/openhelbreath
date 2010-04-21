#ifndef WIDGET_H
#define WIDGET_H

#include "Event.h"
#include "Surface.h"

namespace gui
{

	class Widget: public Event
	{
		public:
			Widget();
			~Widget();

			virtual void Draw(SDL_Surface *Dest);

			virtual void OnEvent(SDL_Event *EventSource);

			void SetPosition(int X, int Y);

			void SetSurface(SDL_Surface *Source);

			SDL_Surface *GetSurface() const;

			int X() const;

			int Y() const;

			int getTag() const
			{
				return Tag;
			}

			void setTag(int Tag)
			{
				this->Tag = Tag;
			}

		private:
			SDL_Surface *WidgetSurface;

			int PosX;

			int PosY;

			int Tag;
	};

	inline SDL_Surface *Widget::GetSurface() const
	{
		return WidgetSurface;
	}

} //namespace gui

#endif // WIDGET_H
