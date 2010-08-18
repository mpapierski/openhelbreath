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
			virtual ~Widget();
			virtual void draw(SDL_Surface* dest);
			virtual void onEvent(SDL_Event* eventSource);
			virtual void setPosition(int x, int y);
			void setSurface(SDL_Surface* source);
			SDL_Surface *getSurface() const;
			int x() const;
			int y() const;
			void setId(int id);
			int getId() const;
			bool isEnabled() const;
			virtual void setEnabled(bool enabled);
			bool isVisible() const;
			virtual void setVisible(bool visible);

		private:
			SDL_Surface* widgetSurface;
			int posX;
			int posY;
			int id;
			bool enabled;
			bool visible;
	};

	inline SDL_Surface* Widget::getSurface() const
	{
		if (widgetSurface != NULL)
			return widgetSurface;
		else
			return NULL;
	}

} // namespace gui

#endif // WIDGET_H
