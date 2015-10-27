
#ifndef INIT_H
#define INIT_H

#include "SDLpp.h"


namespace SDL
{
	class Init
	{
	private:
		static Init instance;
		
		Init();
	public:
		~Init();
		
	};
}


#endif

