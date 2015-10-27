
#include "Cursor.h"

using namespace SDL;


Cursor::Cursor(SDL_Cursor* cursor)
	: cursor(cursor), needsFree(false)
{
}


Cursor::Cursor(const boost::uint8_t *data, const boost::uint8_t *mask, int width, int height, int hotX, int hotY)
	: needsFree(true)
{
  // i know the const_casts aren't good, but SDL should have declared them const. It's not my fault.
  cursor = SDL_CreateCursor(const_cast<boost::uint8_t*>(data), const_cast<boost::uint8_t*>(mask), width, height, hotX, hotY);
}


Cursor::~Cursor()
{
	if (needsFree)
		SDL_FreeCursor(cursor);
}
