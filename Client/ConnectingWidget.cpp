#include "ConnectingWidget.h"
#include "Game.h"

namespace gui
{

	ConnectingWidget::ConnectingWidget()
	{
		setSurface(Surface::createSurface(640, 480, 0, 0, 0, 128));
		setVisible(false);
		setEnabled(false);
		setState(0);
	}

	ConnectingWidget::~ConnectingWidget()
	{

	}

	void ConnectingWidget::draw(SDL_Surface* dest)
	{
		if (!isVisible())
			return;

		Surface::draw(dest, getSurface(), 0, 0);

		int x = 320 - (SpriteBank::manager.getSprite(SPRID_GAMEDIALOG_3).getFrameRect(INTERFACE_DIALOG_MESSAGEBOX).w / 2);
		int y = 240 - (SpriteBank::manager.getSprite(SPRID_GAMEDIALOG_3).getFrameRect(INTERFACE_DIALOG_MESSAGEBOX).h / 2);

		SpriteBank::manager.draw(dest, x, y, SPRID_GAMEDIALOG_3, INTERFACE_DIALOG_MESSAGEBOX);

		char Descr[100];
		switch (state)
		{
			case 0:
				sprintf(Descr, "Connecting to server... %d sec.", messageTimer.getTicks() / 1000);
				Font::putAlignedSprText(dest, x, y + 30, 315, Descr);
				break;
			case 1:
				sprintf(Descr, "Waiting for response... %d sec.", messageTimer.getTicks() / 1000);
				Font::putAlignedSprText(dest, x, y + 30, 315, Descr);
				break;
		}

		if (messageTimer.getTicks() > 7000)
		{
			Font::putAlignedText(dest, x, y + 75, 315, "Press ESC key during long time of no", Font::NORMAL, 0, 0, 0);
			Font::putAlignedText(dest, x, y + 90, 315, "connection and return to the main menu.", Font::NORMAL, 0, 0, 0);
		}
		else
			Font::putAlignedText(dest, x, y + 75, 315, "Connecting to server. Please wait...", Font::NORMAL, 0, 0, 0);
	}

	void ConnectingWidget::setVisible(bool visible)
	{
		Widget::setVisible(visible);
		if (isVisible())
		{
			setState(0);
			messageTimer.start();
			Game::getInstance().mouseCursor.setCursorStyle(Mouse::THINK);
		}
		else
			Game::getInstance().mouseCursor.setCursorStyle(Mouse::ARROW);
	}

	void ConnectingWidget::setState(int state)
	{
		this->state = state;
		messageTimer.start();
	}

	int ConnectingWidget::getState() const
	{
		return this->state;
	}

} //namespace gui
