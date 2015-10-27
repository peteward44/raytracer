
#include "Overlay.h"

using namespace SDL;


Overlay::Overlay(int width, int height, boost::uint32_t format, Surface& surface)
	: lockCount(0)
{
	overlay = SDL_CreateYUVOverlay(width, height, format, surface.surface);
	if (overlay == 0)
		throw SurfaceException("Could not create overlay");
}


Overlay::Overlay(boost::uint32_t format, Surface& surface)
	: lockCount(0)
{
	overlay = SDL_CreateYUVOverlay(surface.GetWidth(), surface.GetHeight(), format, surface.surface);
	if (overlay == 0)
		throw SurfaceException("Could not create overlay");
}


Overlay::~Overlay()
{
	SDL_FreeYUVOverlay(overlay);
}


void Overlay::Display(const Rect& rect)
{
	SDL_Rect sdlRect;
	rect.Convert(sdlRect);
	if (SDL_DisplayYUVOverlay(overlay, &sdlRect) != 0)
		throw SurfaceException("Could not display overlay");
}


boost::uint8_t** Overlay::Lock()
{
	if (SDL_LockYUVOverlay(overlay) != 0)
		throw SurfaceException("Could not lock surface");
	lockCount++;
	return (boost::uint8_t**)overlay->pixels;
}


const boost::uint8_t** Overlay::Lock() const
{
	if (SDL_LockYUVOverlay(overlay) != 0)
		throw SurfaceException("Could not lock surface");
	lockCount++;
	return (const boost::uint8_t**)overlay->pixels;
}


void Overlay::Unlock() const
{
	SDL_UnlockYUVOverlay(overlay);
	lockCount--;
}

