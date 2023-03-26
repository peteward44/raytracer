
#ifndef INIT_H
#define INIT_H

#include "SDLpp.h"


namespace SDL
{
	class Init;
	typedef boost::shared_ptr<Init> InitPtr;

	class Init
	{
	private:
		Init();
	public:
		~Init();
		
		static InitPtr Create();
	};
}


#endif

