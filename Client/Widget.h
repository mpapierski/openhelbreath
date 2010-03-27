#ifndef WIDGET_H
#define WIDGET_H

#include "Event.h"
#include "Surface.h"

class Widget : public Event
{
public:
	Widget();

	~Widget();

	virtual void Draw(SDL_Surface *Dest);

	void OnEvent(SDL_Event *EventSource);

	void SetPosition(int X, int Y);

	void SetSurface(SDL_Surface *Source);

	SDL_Surface *GetSurface() const;

	int X() const;

	int Y() const;

private:
	SDL_Surface *WidgetSurface;

	int PosX;

	int PosY;
};

#endif // WIDGET_H
