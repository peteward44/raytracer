
#ifndef CURSOR_H
#define CURSOR_H

#include "SDLpp.h"
#include <boost/shared_ptr.hpp>


namespace SDL
{
	class Cursor
	{
	private:
		Cursor();
		Cursor(const Cursor& cursor);
		Cursor& operator = (const Cursor& cursor);
		
		SDL_Cursor* cursor;
		bool needsFree;
	
	public:
		Cursor(SDL_Cursor* cursor);
		Cursor(const boost::uint8_t *data, const boost::uint8_t *mask, int width, int height, int hotX, int hotY);
		~Cursor();

		inline const SDL_Cursor* GetCursor() const
		  { return cursor; }

		inline SDL_Cursor* GetCursor()
		  { return cursor; }
	};
	
	
	typedef boost::shared_ptr< Cursor > Cursor_t;
}


#endif

