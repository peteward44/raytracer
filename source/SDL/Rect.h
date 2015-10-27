
#ifndef RECT_H
#define RECT_H

#include "SDLpp.h"


namespace SDL
{
	class Rect
	{
	private:

	public:
		inline Rect()
		{}
		
		inline Rect(SDL_Rect& rect)
			: X(rect.x), Y(rect.y), Width(rect.w), Height(rect.h)
		{}
		
		inline Rect(boost::int16_t x, boost::int16_t y, boost::uint16_t width, boost::uint16_t height)
			: X(x), Y(y), Width(width), Height(height)
		{}

		inline void Convert(SDL_Rect& rect) const
		  {
		    rect.x = X;
		    rect.y = Y;
		    rect.w = Width;
		    rect.h = Height;
		  }

		boost::int16_t X, Y;
		boost::uint16_t Width, Height;
	};
}


#endif
