
#ifndef COLOR_H
#define COLOR_H

#include "SDLpp.h"


namespace SDL
{
	class Color
	{
	public:
		boost::uint8_t R, G, B, A;

		inline Color(boost::uint8_t r = 0, boost::uint8_t g = 0, boost::uint8_t b = 0, boost::uint8_t a = 0)
			: R(r), G(g), B(b), A(a)
		{}
	};
}

#endif
