
#include "Surface.h"
#include <cassert>


using namespace SDL;


Surface::Surface(SDL_Surface* surface, bool needsFree)
	: surface(surface), pixelData(0), clippingRect(surface->clip_rect), pixelFormat(surface->format),
		lockCount(0), needsFree(needsFree)
{
}


Surface::Surface(SDL_Surface* surface, bool needsFree, boost::uint8_t* pixelData)
	: surface(surface), pixelData(pixelData), clippingRect(surface->clip_rect), pixelFormat(surface->format),
		lockCount(0), needsFree(needsFree)
{
}


Surface::~Surface()
{
	if (needsFree)
	{
		SDL_FreeSurface(surface);
		delete[] pixelData;
	}
}


boost::uint8_t* Surface::Lock()
{
	if (SDL_MUSTLOCK(surface))
	{
		if (SDL_LockSurface(surface) != 0)
			throw SurfaceException("Could not lock surface");
	}
	lockCount++;
	return (boost::uint8_t*)surface->pixels;
}


const boost::uint8_t* Surface::Lock() const
{
	if (SDL_MUSTLOCK(surface))
	{
		if (SDL_LockSurface(surface) != 0)
			throw SurfaceException("Could not lock surface");
	}
	lockCount++;
	return (const boost::uint8_t*)surface->pixels;
}


void Surface::Unlock() const
{
	if (lockCount == 0)
		throw SurfaceException("Surface not locked");
	if (SDL_MUSTLOCK(surface))
		SDL_UnlockSurface(surface);
	lockCount--;
}


void Surface::Update(const Rect& rect)
{
	assert(lockCount == 0);
	SDL_UpdateRect(surface, rect.X, rect.Y, rect.Width, rect.Height);
}


void Surface::Update()
{
	Update(Rect(0, 0, 0, 0));
}


void Surface::FillRect(const Rect& rect, const Color& color)
{
	SDL_Rect sdlRect;
	sdlRect.x = rect.X;
	sdlRect.y = rect.Y;
	sdlRect.w = rect.Width;
	sdlRect.h = rect.Height;
	if (SDL_FillRect(surface, &sdlRect, pixelFormat.ColorToUInt32(color)) != 0)
		throw SurfaceException("Could not fill rect");
}


void Surface::Fill(const Color& color)
{
	if (SDL_FillRect(surface, 0, pixelFormat.ColorToUInt32(color)) != 0)
		throw SurfaceException("Could not fill rect");
}


void Surface::SaveBMP(const std::string& fileName) const
{
	if (SDL_SaveBMP(surface, fileName.c_str()) != 0)
		throw SurfaceException("Could not save BMP");
}


void Surface::Flip()
{
	if (SDL_Flip(surface) != 0)
		throw SurfaceException("Could not flip surface");
}


void Surface::PutPixel(int x, int y, const Color& color)
{
	assert(lockCount > 0);

	int bpp = pixelFormat.GetBytesPerPixel();
	boost::uint32_t pixel = pixelFormat.ColorToUInt32(color);
	boost::uint8_t* position = (boost::uint8_t*)surface->pixels + y * surface->pitch + x * bpp;

	switch (bpp)
	{
	case 1:
		*position = (boost::uint8_t)pixel;
		break;

	case 2:
		*(boost::uint16_t*)position = (boost::uint16_t)pixel;
		break;

	case 3:
		if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
		{
			position[0] = (boost::uint8_t)((pixel >> 16) & 0xff);
			position[1] = (boost::uint8_t)((pixel >> 8) & 0xff);
			position[2] = (boost::uint8_t)(pixel & 0xff);
		}
		else
		{
			position[0] = (boost::uint8_t)(pixel & 0xff);
			position[1] = (boost::uint8_t)((pixel >> 8) & 0xff);
			position[2] = (boost::uint8_t)((pixel >> 16) & 0xff);
		}
		break;

	case 4:
		*(boost::uint32_t*)position = pixel;
		break;
	}
}


Color Surface::GetPixel(int x, int y)
{
	assert(lockCount > 0);

  int bpp = pixelFormat.GetBytesPerPixel();
	boost::uint32_t colorInt;
  boost::uint8_t* position = (boost::uint8_t*)surface->pixels + y * surface->pitch + x * bpp;

  switch (bpp)
	{
  case 1:
    colorInt = *position;

  case 2:
		colorInt = *(boost::uint16_t*)position;

  case 3:
		if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
			colorInt = position[0] << 16 | position[1] << 8 | position[2];
		else
			colorInt = position[0] | position[1] << 8 | position[2] << 16;

  case 4:
    colorInt = *(boost::uint32_t*)position;

  default:
		colorInt = 0;
  }

	return pixelFormat.Int32ToColor(colorInt);
}


void Surface::SetClippingArea(const Rect& rect)
{
  SDL_Rect sdlRect;
  rect.Convert(sdlRect);
	SDL_SetClipRect(surface, &sdlRect);
}


Rect Surface::GetClippingArea() const
{
	SDL_Rect rect;
	SDL_GetClipRect(surface, &rect);
	return Rect(rect);
}


void Surface::SetColorKey(const Color& colour, bool useRLE)
{
	if (SDL_SetColorKey(surface, pixelFormat.ColorToUInt32(colour), SDL_SRCCOLORKEY | (useRLE ? SDL_RLEACCEL : 0)) == -1)
		throw SurfaceException("Could not set colour key");
}


SurfacePtr Surface::Load(const std::string& fileName)
{
#ifndef USE_SDL_IMAGE
	SDL_Surface* surface = SDL_LoadBMP(fileName.c_str());
#else
	SDL_Surface* surface = IMG_Load(fileName.c_str());
#endif

	if (surface == 0)
		throw SurfaceException("BMP could not be loaded");
	return SurfacePtr(new Surface(surface, true));
}


SurfacePtr Surface::CreateRGBSurface(boost::uint32_t flags, int width, int height, int depth,
			boost::uint32_t rmask, boost::uint32_t gmask, boost::uint32_t bmask, boost::uint32_t amask)
{
	SDL_Surface* surface = SDL_CreateRGBSurface(flags, width, height, depth, rmask, gmask, bmask, amask);
	if (surface == 0)
		throw SurfaceException("Surface could not be created");
	return SurfacePtr(new Surface(surface, true));
}


SurfacePtr Surface::CreateRGBSurfaceFrom(const boost::uint8_t *pixels, int width, int height,
			int depth, int pitch, Uint32 rmask, Uint32 gmask, Uint32 bmask, Uint32 amask)
{
	// create a copy of the pixel data - SDL operates on the data passed so to keep things safe we create our
	// own copy
	unsigned int amount = width * pitch * (depth/8);
	boost::uint8_t* data = new boost::uint8_t[ amount ];
	memcpy(data, pixels, amount);
	
	SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(data, width, height, depth, pitch, rmask, gmask, bmask, amask);
	if (surface == 0)
		throw SurfaceException("Surface could not be created");
	return SurfacePtr(new Surface(surface, true, data));
}


SurfacePtr Surface::ConvertSurfaceToDisplayFormat(const SurfacePtr& surface)
{
	SDL_Surface* sdlSurface = SDL_DisplayFormat(const_cast<SDL_Surface*>(surface->surface));
	if (sdlSurface == 0)
		throw SurfaceException("Could not convert surface");
	return SurfacePtr(new Surface(sdlSurface, true));
}


SurfacePtr Surface::ConvertSurfaceToDisplayFormatAlpha(const SurfacePtr& surface)
{
	SDL_Surface* sdlSurface = SDL_DisplayFormatAlpha(const_cast<SDL_Surface*>(surface->surface));
	if (sdlSurface == 0)
		throw SurfaceException("Could not convert surface");
	return SurfacePtr(new Surface(sdlSurface, true));
}


SurfacePtr Surface::CloneSurface(const SurfacePtr& surface)
{
	return ConvertSurface(surface, surface->GetFlags());
}


SurfacePtr Surface::ConvertSurface(const SurfacePtr& surface, boost::uint32_t flags)
{
	return ConvertSurface(surface, surface->pixelFormat, flags);
}


SurfacePtr Surface::ConvertSurface(const SurfacePtr& surface, const PixelFormat& pixelFormat, boost::uint32_t flags)
{
	// TODO: pixeldata need to be copied??
	SDL_Surface* sdlSurface = SDL_ConvertSurface(const_cast<SDL_Surface*>(surface->surface), const_cast<SDL_PixelFormat*>(pixelFormat.pixelFormat), flags);
	if (sdlSurface == 0)
		throw SurfaceException("Could not convert surface");
	return SurfacePtr(new Surface(sdlSurface, true));
}


void Surface::Blit(int x, int y, const SurfacePtr& srcSurface)
{
	SDL_Rect sdlRect;
	sdlRect.x = x;
	sdlRect.y = y;
	switch (SDL_BlitSurface(const_cast<SDL_Surface*>(srcSurface->surface), 0, this->surface, &sdlRect))
	{
	case -1:
		throw SurfaceException("Blit failed");
	break;
	case -2:
		throw SurfaceLostException();
	break;
	}
}


void Surface::Blit(int x, int y, const SurfacePtr& srcSurface, const Rect& rect)
{
	SDL_Rect sdlRect, sdlRect2;
	sdlRect.x = x;
	sdlRect.y = y;

	rect.Convert(sdlRect2);

	switch (SDL_BlitSurface(const_cast<SDL_Surface*>(srcSurface->surface), &sdlRect2, this->surface, &sdlRect))
	{
	case -1:
		throw SurfaceException("Blit failed");
	break;
	case -2:
		throw SurfaceLostException();
	break;
	}
}

