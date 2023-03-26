
#ifndef SURFACE_H
#define SURFACE_H

#include "SDLpp.h"
#include "PixelFormat.h"
#include "Rect.h"
#include "Color.h"
#include <boost/shared_ptr.hpp>


namespace SDL
{
	class Surface;
	typedef boost::shared_ptr<Surface> SurfacePtr;

	/// <summary>
	/// Represents an SDL surface.
	/// </summary>
	class Surface
	{
		friend class Window;

	private:
		SDL_Surface* surface;
		boost::uint8_t* pixelData;
		Rect clippingRect;
		PixelFormat pixelFormat;
		mutable int lockCount;
		bool needsFree;

		Surface(const Surface& surface);
		Surface& operator= (Surface& surface);

		Surface();
		Surface(SDL_Surface* surface, bool needsFree);
		Surface(SDL_Surface* surface, bool needsFree, boost::uint8_t* pixelData);
		
	public:
		/// <summary>
		/// Surface destructor
		/// </summary>
		~Surface();
		
		/// <summary>
		/// Gets the width of surface
		/// </summary>
		/// <returns>Width of surface</returns>
		inline boost::int16_t GetWidth() const
		{ return surface->w; }

		/// <summary>
		/// Gets the height of the surface
		/// </summary>
		/// <returns>Height of the surface</returns>
		inline boost::int16_t GetHeight() const
		{ return surface->h; }

		/// <summary>
		/// Gets the pitch of the surface
		/// </summary>
		/// <returns>Pitch of the surface</returns>
		inline boost::uint16_t GetPitch() const
		{ return surface->pitch; }

		/// <summary>
		/// Gets the pixelformat of the surface
		/// </summary>
		/// <returns>Pixelformat of the surface</returns>
		inline const PixelFormat& GetPixelFormat() const
		{ return pixelFormat; }

		/// <summary>
		/// Gets the flags of the surface
		/// </summary>
		/// <returns>Flags of the surface</returns>
		inline boost::uint16_t GetFlags() const
		{ return surface->flags; }

		/// <summary>
		/// Gets the clipping rect
		/// </summary>
		/// <returns>Clipping rectangle</returns>
		inline const Rect& GetClippingRect() const
		{ return clippingRect; }

		/// <summary>
		/// Is the surface locked?
		/// </summary>
		/// <returns>True if the surface is locked, false otherwise</returns>
		inline bool IsLocked() const
		{ return lockCount > 0; }

		/// <summary>
		/// Locks the surface
		/// </summary>
		/// <returns>Array of pixel data</returns>
		boost::uint8_t* Lock();
		
		/// <summary>
		/// Locks the surface
		/// </summary>
		/// <returns>Array of pixel data</returns>
		const boost::uint8_t* Lock() const;
		
		/// <summary>
		/// Unlocks the surface
		/// </summary>
		void Unlock() const;

		/// <summary>
		/// Puts a pixel on the screen with the specified coordinates. Surface must be locked beforehand.
		/// </summary>
		/// <param name="x">X position</param>
		/// <param name="y">Y position</param>
		/// <param name="color">Colour of the pixel</param>
		void PutPixel(int x, int y, const Color& color);
		
		/// <summary>
		/// Gets a pixel on the screen from the specified coordinates. Surface must be locked beforehand.
		/// </summary>
		/// <param name="x">X position</param>
		/// <param name="y">Y position</param>
		/// <returns>Pixel colour</returns>
		Color GetPixel(int x, int y);

		/// <summary>
		/// Fills a rectangle with the specified colour
		/// </summary>
		/// <param name="rect">Rectangle to fill</param>
		/// <param name="color">Colour to fill it with</param>
		void FillRect(const Rect& rect, const Color& color);
		
		/// <summary>
		/// Fills the entire screen with the colour
		/// </summary>
		/// <param name="color">Colour to fill it with</param>
		void Fill(const Color& color);

		/// <summary>
		/// Sets the clipping area
		/// </summary>
		/// <param name="rect">Rectangle representing the clipping area</param>				
		void SetClippingArea(const Rect& rect);

		/// <summary>
		/// Blits srcSurface to the surface at the specified coordinates
		/// </summary>
		/// <param name="x">X coordinate</param>
		/// <param name="y">Y coordinate</param>
		/// <param name="srcSurface">Source surface for blitting</param>
		void Blit(int x, int y, const SurfacePtr& srcSurface);
		
		/// <summary>
		/// Blits the portion of srcSurface specified by rect to the surface at the given coordinates
		/// </summary>
		/// <param name="x">X coordinate</param>
		/// <param name="y">Y coordinate</param>
		/// <param name="srcSurface">Source surface for blitting</param>
		/// <param name="rect">Rectangle part of srcSurface to blit</param>
		void Blit(int x, int y, const SurfacePtr& srcSurface, const Rect& rect);

		/// <summary>
		/// Gets the clipping area
		/// </summary>
		/// <returns>Rectangle representing the clipping area</returns>
		Rect GetClippingArea() const;
		
		/// <summary>
		/// Enable colour key
		/// </summary>
		/// <param name="colour">Colour to use for transparency</param>
		/// <param name="useRLE">Enable RLE encoding</param>
		void SetColorKey(const Color& colour, bool useRLE);

		/// <summary>
		/// Saves the surface as a bitmap
		/// </summary>
		/// <param name="fileName">Filename of bitmap</param>
		void SaveBMP(const std::string& fileName) const;		
		
		/// <summary>
		/// Loads an image into a surface. If USE_SDL_IMAGE is defined it can support all image formats,
		/// if not only .bmp will be supported
		/// </summary>
		/// <param name="fileName">Filename of image</param>		
		/// <returns>Surface pointer</returns>
		static SurfacePtr Load(const std::string& fileName);

		/// <summary>
		/// Creates an empty RGB surface
		/// </summary>
		/// <param name="flags">Flags of the surface</param>
		/// <param name="width">Width of the surface</param>
		/// <param name="height">Height of the surface</param>
		/// <param name="depth">Bit depth of the surface</param>
		/// <param name="rmask">Red mask</param>
		/// <param name="gmask">Green mask</param>
		/// <param name="bmask">Blue mask</param>
		/// <param name="amask">Alpha mask</param>
		/// <returns>Pointer to a surface</returns>
		static SurfacePtr CreateRGBSurface(boost::uint32_t flags, int width, int height, int depth,
			boost::uint32_t rmask, boost::uint32_t gmask, boost::uint32_t bmask, boost::uint32_t amask);

		/// <summary>
		/// Creates an RGB surface from pixel data
		/// </summary>
		/// <param name="pixels">Pixel data</param>
		/// <param name="width">Width of the surface</param>
		/// <param name="height">Height of the surface</param>
		/// <param name="depth">Bit depth of the surface</param>
		/// <param name="pitch">Pitch of the surface data</param>
		/// <param name="rmask">Red mask</param>
		/// <param name="gmask">Green mask</param>
		/// <param name="bmask">Blue mask</param>
		/// <param name="amask">Alpha mask</param>
		/// <returns>Pointer to a surface</returns>
		static SurfacePtr CreateRGBSurfaceFrom(const boost::uint8_t* pixels, int width, int height,
			int depth, int pitch, Uint32 rmask, Uint32 gmask, Uint32 bmask, Uint32 amask);

		/// <summary>
		/// Clones a surface
		/// </summary>
		/// <param name="surface">Surface to clone</param>
		/// <returns>New surface</returns>
		static SurfacePtr CloneSurface(const SurfacePtr& surface);

		/// <summary>
		/// Converts one surface to another
		/// </summary>
		/// <param name="surface">Surface to copy</param>
		/// <param name="flags">Hardware flags</param>
		/// <returns>Converted surface</returns>
		static SurfacePtr ConvertSurface(const SurfacePtr& surface, boost::uint32_t flags);
				
		/// <summary>
		/// Converts one surface to another
		/// </summary>
		/// <param name="surface">Surface to copy</param>
		/// <param name="pixelFormat">Pixelformat to use</param>
		/// <param name="flags">Hardware flags</param>
		/// <returns>Converted surface</returns>		
		static SurfacePtr ConvertSurface(const SurfacePtr& surface, const PixelFormat& pixelFormat, boost::uint32_t flags);
	};
}


#endif
