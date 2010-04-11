#include "Widget.h"

Widget::Widget()
{
	WidgetSurface = NULL;

	PosX = 0;
	PosY = 0;
}

void Widget::Draw(SDL_Surface *Dest)
{
	Surface::Draw(Dest, WidgetSurface, PosX, PosY);
}

void Widget::OnEvent(SDL_Event *EventSource)
{
	Event::OnEvent(EventSource);
}

void Widget::SetPosition(int X, int Y)
{
	PosX = X;
	PosY = Y;
}

void Widget::SetSurface(SDL_Surface *Source)
{
	WidgetSurface = Source;
}

int Widget::X() const
{
	return PosX;
}

int Widget::Y() const
{
	return PosY;
}

Widget::~Widget()
{
	SDL_FreeSurface(WidgetSurface);
}
