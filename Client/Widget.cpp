#include "Widget.h"

namespace gui
{

	Widget::Widget()
	{
		widgetSurface = NULL;
		setId(0);
		setPosition(0, 0);
		setEnabled(true);
		setVisible(true);
	}

	Widget::~Widget()
	{
		SDL_FreeSurface(widgetSurface);
	}

	void Widget::draw(SDL_Surface* dest)
	{
		if(!visible)
			return;

		Surface::draw(dest, widgetSurface, posX, posY);
	}

	void Widget::onEvent(SDL_Event* eventSource)
	{
		if(!enabled)
			return;

		Event::onEvent(eventSource);
	}

	void Widget::setPosition(int x, int y)
	{
		posX = x;
		posY = y;
	}

	void Widget::setSurface(SDL_Surface* source)
	{
		if(source != NULL)
		{
			widgetSurface = SDL_ConvertSurface(source, source->format, source->flags);
			SDL_FreeSurface(source);
		}
		else
			widgetSurface = NULL;
	}

	int Widget::x() const
	{
		return posX;
	}

	int Widget::y() const
	{
		return posY;
	}

	void Widget::setId(int id)
	{
		this->id = id;
	}

	int Widget::getId() const
	{
		return id;
	}

	bool Widget::isEnabled() const
	{
		return enabled;
	}

	void Widget::setEnabled(bool enabled)
	{
		this->enabled = enabled;
	}

	bool Widget::isVisible() const
	{
		return visible;
	}

	void Widget::setVisible(bool visible)
	{
		this->visible = visible;
	}

} //namespace gui
