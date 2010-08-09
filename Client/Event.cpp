#include "Event.h"

Event::Event()
{

}

Event::~Event()
{

}

void Event::onEvent(SDL_Event* eventSource)
{
	switch (eventSource->type)
	{
		case SDL_ACTIVEEVENT:
		{
			switch (eventSource->active.state)
			{
				case SDL_APPMOUSEFOCUS:
				{
					if (eventSource->active.gain)
						onMouseFocus();
					else
						onMouseBlur();
					break;
				}
				case SDL_APPINPUTFOCUS:
				{
					if (eventSource->active.gain)
						onInputFocus();
					else
						onInputBlur();
					break;
				}
				case SDL_APPACTIVE:
				{
					if (eventSource->active.gain)
						onRestore();
					else
						onMinimize();
					break;
				}
			}
			break;
		}

		case SDL_KEYDOWN:
		{
			onKeyDown(eventSource->key.keysym.sym, eventSource->key.keysym.mod,
					eventSource->key.keysym.unicode);
			break;
		}

		case SDL_KEYUP:
		{
			onKeyUp(eventSource->key.keysym.sym, eventSource->key.keysym.mod,
					eventSource->key.keysym.unicode);
			break;
		}

		case SDL_MOUSEMOTION:
		{
			onMouseMove(eventSource->motion.x, eventSource->motion.y, eventSource->motion.xrel,
					eventSource->motion.yrel, (eventSource->motion.state & SDL_BUTTON(
							SDL_BUTTON_LEFT)) != 0, (eventSource->motion.state & SDL_BUTTON(
							SDL_BUTTON_RIGHT)) != 0, (eventSource->motion.state & SDL_BUTTON(
							SDL_BUTTON_MIDDLE)) != 0);
			break;
		}

		case SDL_MOUSEBUTTONDOWN:
		{
			switch (eventSource->button.button)
			{
				case SDL_BUTTON_LEFT:
				{
					onLButtonDown(eventSource->button.x, eventSource->button.y);
					break;
				}
				case SDL_BUTTON_RIGHT:
				{
					onRButtonDown(eventSource->button.x, eventSource->button.y);
					break;
				}
				case SDL_BUTTON_MIDDLE:
				{
					onMButtonDown(eventSource->button.x, eventSource->button.y);
					break;
				}
			}
			break;
		}

		case SDL_MOUSEBUTTONUP:
		{
			switch (eventSource->button.button)
			{
				case SDL_BUTTON_LEFT:
				{
					onLButtonUp(eventSource->button.x, eventSource->button.y);
					break;
				}
				case SDL_BUTTON_RIGHT:
				{
					onRButtonUp(eventSource->button.x, eventSource->button.y);
					break;
				}
				case SDL_BUTTON_MIDDLE:
				{
					onMButtonUp(eventSource->button.x, eventSource->button.y);
					break;
				}
			}
			break;
		}

		case SDL_JOYAXISMOTION:
		{
			onJoyAxis(eventSource->jaxis.which, eventSource->jaxis.axis, eventSource->jaxis.value);
			break;
		}

		case SDL_JOYBALLMOTION:
		{
			onJoyBall(eventSource->jball.which, eventSource->jball.ball, eventSource->jball.xrel,
					eventSource->jball.yrel);
			break;
		}

		case SDL_JOYHATMOTION:
		{
			onJoyHat(eventSource->jhat.which, eventSource->jhat.hat, eventSource->jhat.value);
			break;
		}
		case SDL_JOYBUTTONDOWN:
		{
			onJoyButtonDown(eventSource->jbutton.which, eventSource->jbutton.button);
			break;
		}

		case SDL_JOYBUTTONUP:
		{
			onJoyButtonUp(eventSource->jbutton.which, eventSource->jbutton.button);
			break;
		}

		case SDL_QUIT:
		{
			onExit();
			break;
		}

		case SDL_SYSWMEVENT:
		{
			//Ignore
			break;
		}

		case SDL_VIDEORESIZE:
		{
			onResize(eventSource->resize.w, eventSource->resize.h);
			break;
		}

		case SDL_VIDEOEXPOSE:
		{
			onExpose();
			break;
		}
		case SDL_USEREVENT:
			onUser(eventSource->user.type, eventSource->user.code, eventSource->user.data1, eventSource->user.data2);
			break;
		default:
		{
			fprintf(stderr, "Unknown SDL event : %d\n", eventSource->type);
			break;
		}
	}
}

void Event::onInputFocus()
{
	// pure virtual
}

void Event::onInputBlur()
{
	// pure virtual
}

void Event::onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	// pure virtual
}

void Event::onKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	// pure virtual
}

void Event::onMouseFocus()
{
	// pure virtual
}

void Event::onMouseBlur()
{
	// pure virtual
}

void Event::onMouseMove(int x, int y, int relX, int relY, bool left, bool right, bool middle)
{
	// pure virtual
}

void Event::onMouseWheel(bool up, bool down)
{
	// pure virtual
}

void Event::onLButtonDown(int x, int y)
{
	// pure virtual
}

void Event::onLButtonUp(int x, int y)
{
	// pure virtual
}

void Event::onRButtonDown(int x, int y)
{
	// pure virtual
}

void Event::onRButtonUp(int mX, int mY)
{
	// pure virtual
}

void Event::onMButtonDown(int x, int y)
{
	// pure virtual
}

void Event::onMButtonUp(int x, int y)
{
	// pure virtual
}

void Event::onJoyAxis(Uint8 which, Uint8 axis, Sint16 value)
{
	// pure virtual
}

void Event::onJoyButtonDown(Uint8 which, Uint8 button)
{
	// pure virtual
}

void Event::onJoyButtonUp(Uint8 which, Uint8 button)
{
	// pure virtual
}

void Event::onJoyHat(Uint8 which, Uint8 hat, Uint8 value)
{
	// pure virtual
}

void Event::onJoyBall(Uint8 which, Uint8 ball, Sint16 relX, Sint16 relY)
{
	// pure virtual
}

void Event::onMinimize()
{
	// pure virtual
}

void Event::onRestore()
{
	// pure virtual
}

void Event::onResize(int w, int h)
{
	// pure virtual
}

void Event::onExpose()
{
	// pure virtual
}

void Event::onExit()
{
	// pure virtual
}

void Event::onUser(Uint8 type, int code, void* data1, void* data2)
{
	// pure virtual
}
