
#ifndef OVERLAY_H
#define OVERLAY_H

#include "SDLpp.h"
#include "Surface.h"
#include <cassert>


namespace SDL
{
	class Overlay
	{
	private:
		SDL_Overlay* overlay;
		mutable int lockCount;
		
	public:
		Overlay(int width, int height, boost::uint32_t format, Surface& surface);
		Overlay(boost::uint32_t format, Surface& surface);
		~Overlay();
		
		
		inline int GetWidth() const
		{ return overlay->w; }
		
		inline int GetHeight() const
		{ return overlay->h; }
		
		inline int GetFormat() const
		{ return overlay->format; }
		
		inline int GetNumPlanes() const
		{ return overlay->planes; }
		
		inline bool IsHardware() const
		{ return overlay->hw_overlay ? 1 : 0; }
		
		inline bool IsLocked() const
		{ return lockCount > 0; }
		
		inline int GetPitch(int plane) const
		{
			assert(plane >= 0 && plane < overlay->planes);
			return overlay->pitches[plane];
		}
		
		
		void Display(const Rect& rect);
		
		boost::uint8_t** Lock();
		const boost::uint8_t** Lock() const;
		void Unlock() const;
	};
}


#endif
