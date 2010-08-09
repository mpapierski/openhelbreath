#ifndef LABEL_H
#define LABEL_H

#include "Widget.h"
#include "Font.h"

namespace gui
{

	class Label : public Widget
	{
		public:
			Label();
			virtual ~Label();
			void draw(SDL_Surface* dest);
			void setText(const std::string& text);
			const std::string& getText() const;

		private:
			std::string labelText;
	};

} // namespace gui

#endif // LABEL_H
