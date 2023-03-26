
#ifndef PIXELFORMAT_H
#define PIXELFORMAT_H

#include "SDLpp.h"
#include "Color.h"


namespace SDL
{
	class PixelFormat
	{
		friend class Surface;
		
	private:
		SDL_PixelFormat* pixelFormat;

	public:
		inline PixelFormat(SDL_PixelFormat* pixelFormat)
			: pixelFormat(pixelFormat)
		{}
		
		inline boost::uint8_t GetBitsPerPixel() const
		{ return pixelFormat->BitsPerPixel; }
		
		inline boost::uint8_t GetBytesPerPixel() const
		{ return pixelFormat->BytesPerPixel; }
		
		inline boost::uint32_t GetRedMask() const
		{ return pixelFormat->Rmask; }
		
		inline boost::uint32_t GetGreenMask() const
		{ return pixelFormat->Gmask; }
		
		inline boost::uint32_t GetBlueMask() const
		{ return pixelFormat->Bmask; }
		
		inline boost::uint32_t GetAlphaMask() const
		{ return pixelFormat->Amask; }
		
		inline boost::uint8_t GetRedShift() const
		{ return pixelFormat->Rshift; }
		
		inline boost::uint8_t GetGreenShift() const
		{ return pixelFormat->Gshift; }
		
		inline boost::uint8_t GetBlueShift() const
		{ return pixelFormat->Bshift; }
		
		inline boost::uint8_t GetAlphaShift() const
		{ return pixelFormat->Ashift; }
		
		inline boost::uint8_t GetRedLoss() const
		{ return pixelFormat->Rloss; }
		
		inline boost::uint8_t GetGreenLoss() const
		{ return pixelFormat->Gloss; }
		
		inline boost::uint8_t GetBlueLoss() const
		{ return pixelFormat->Bloss; }
		
		inline boost::uint8_t GetAlphaLoss() const
		{ return pixelFormat->Aloss; }
		
		inline const SDL_Palette* GetPalette() const
		{ return pixelFormat->palette; }
		
		inline SDL_Palette* GetPalette()
		{ return pixelFormat->palette; }
		
		inline boost::uint32_t ColorToUInt32(const Color& color) const
		{
			return SDL_MapRGBA(pixelFormat, color.R, color.G, color.B, color.A);
		}
		
		inline Color Int32ToColor(boost::uint32_t i) const
		{
			Color color;
			SDL_GetRGBA(i, pixelFormat, &color.R, &color.G, &color.B, &color.A);
			return color;
		}
	};
}

#endif
