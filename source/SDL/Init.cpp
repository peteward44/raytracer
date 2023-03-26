

#include "Init.h"

using namespace SDL;

InitPtr Init::Create() {
	return InitPtr(new Init());
}

Init::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		throw Exception("Could not initialise video subsystem");
		
#ifdef USE_SDL_NET
	if (SDLNet_Init() < 0)
		throw Exception("Could not initialise network subsystem");
#endif
}


Init::~Init()
{
#ifdef USE_SDL_NET
	SDLNet_Quit();
#endif

	SDL_Quit();
}

