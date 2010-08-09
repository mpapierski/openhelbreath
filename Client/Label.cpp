#include "Label.h"

namespace gui
{

	Label::Label()
	{

	}

	Label::~Label()
	{

	}

	void Label::draw(SDL_Surface* dest)
	{
		int prevNewLineCharPos;
		int nextNewLineCharPos;

		prevNewLineCharPos = labelText.find('\n', 0);

		if (prevNewLineCharPos > 0)
		{
			Font::putTextShaded(dest, x(), y(), labelText.substr(0, prevNewLineCharPos), Font::NORMAL, 255, 255, 255);

			int i = 1;
			do
			{
				nextNewLineCharPos = labelText.find('\n', (prevNewLineCharPos + 1));
				if (nextNewLineCharPos > prevNewLineCharPos)
				{
					Font::putTextShaded(dest, x(), (y() + (i * 14)),
							labelText.substr((prevNewLineCharPos + 1), (nextNewLineCharPos
									- prevNewLineCharPos - 1)), Font::NORMAL, 255, 255, 255);
				}
				else
					Font::putTextShaded(dest, x(), (y() + (i * 14)), labelText.substr(
							(prevNewLineCharPos + 1), (labelText.size() - 1)), Font::NORMAL, 255, 255, 255);

				prevNewLineCharPos = nextNewLineCharPos;
				i++;
			} while (nextNewLineCharPos != -1);
		}
		else
			Font::putTextShaded(dest, x(), y(), labelText, Font::NORMAL, 255, 255, 255);
	}

	void Label::setText(const std::string& text)
	{
		labelText = text;
	}

	const std::string& Label::getText() const
	{
		return labelText;
	}
}
