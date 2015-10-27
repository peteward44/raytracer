
#ifndef TIMER_H
#define TIMER_H

#include "SDLpp.h"
#include <boost/function.hpp>


namespace SDL
{
	class Timer
	{
	private:
		boost::uint32_t last;

	public:
		Timer();

		/// <summary>
		/// Returns the time passed (in milliseconds) since this function was last called.
		/// Returns 0 on first time it's called
		/// </summary>
		/// <returns></returns>
		boost::uint32_t GetElapsedTime();
	};
	
	
	class TimerTask
	{
		typedef boost::function0<boost::uint32_t> func_t;
		
	private:
		func_t callback;
		SDL_TimerID id;
		
		static Uint32 StaticCallback(Uint32 interval, void* param);
		
		TimerTask(const TimerTask& copy);
		TimerTask& operator = (const TimerTask& copy);
	
	public:
		TimerTask(boost::uint32_t interval, func_t func);
		
		void Cancel();
	};
}


#endif

