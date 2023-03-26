
#ifndef SDLPP_H
#define SDLPP_H

#include "SDL.h"
#include <boost/cstdint.hpp>
#include <boost/shared_ptr.hpp>

#ifdef WIN32

#pragma warning( push )
#pragma warning( disable : 4251 4275 4099 ) // disables warnings from boost::signal in MSVC

#endif

#include <boost/signals2.hpp>

#ifdef WIN32

#pragma warning( pop )

#endif

#include "Exception.h"


//#define USE_SDL_IMAGE
//#define USE_SDL_NET


#ifdef USE_SDL_IMAGE
#include "SDL_image.h"
#ifdef WIN32
#pragma comment(lib, "SDL_image.lib")
#endif
#endif


#ifdef USE_SDL_NET
#include "SDL_net.h"
#ifdef WIN32
#pragma comment(lib, "SDL_net.lib")
#endif
#endif


#endif

