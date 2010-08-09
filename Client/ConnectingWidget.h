#ifndef CONNECTINGWIDGET_H
#define CONNECTINGWIDGET_H

#include "Widget.h"
#include "Font.h"
#include "Timer.h"

namespace gui
{

	class ConnectingWidget : public Widget
	{
		public:
			ConnectingWidget();
			~ConnectingWidget();
			void draw(SDL_Surface* dest);
			void setVisible(bool visible);
			void setState(int State);
			int getState() const;

		private:
			Timer messageTimer;
			int state;
	};

} // namespace gui
#endif // CONNECTINGWIDGET_H
