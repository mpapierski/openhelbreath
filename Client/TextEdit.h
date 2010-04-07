#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include "Widget.h"
#include "Font.h"

class TextEdit : public Widget
{
public:
	TextEdit();
	~TextEdit();

	TextEdit(const std::string &Text);

	void Draw(SDL_Surface *Dest);

	const std::string &GetText();

	void OnMouseMove(int X, int Y, int RelX, int RelY, bool Left, bool Right, bool Middle);

	void OnLButtonDown(int X, int Y);

	void OnKeyDown(SDLKey Sym, SDLMod Mod, Uint16 Unicode);

	void SetEnabled(bool Enable);

	void SetCursorVisible(bool Visible);

	void SetCursorPosition(int Position);

	void SetMaxLength(int Length);

	void SetPasswordMode(bool Visible);

	void SetText(const std::string &Text);

	void Update();

private:
	void Create();

	SDL_Surface *CursorSurface;

	std::string WidgetText;

	bool Enabled;

	bool PasswordMode;

	bool CursorVisible;

	int CursorPosition;

	unsigned int MaxLength;

	int Blink;
};

#endif // TEXTEDIT_H
