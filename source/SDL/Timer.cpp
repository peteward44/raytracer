
#include "Timer.h"
#include <cassert>


namespace SDL
{

Timer::Timer()
	: last(0)
{
}


boost::uint32_t Timer::GetElapsedTime()
{
	boost::uint32_t time = SDL_GetTicks();
	if (last == 0)
	{
		last = time;
		return 0;
	}
	else
	{
		boost::uint32_t ret = time - last;
		last = time;
		return ret;
	}
}


TimerTask::TimerTask(boost::uint32_t interval, func_t func)
{
	callback = func;
	id = SDL_AddTimer(interval, TimerTask::StaticCallback, this);
	if (id == 0)
		throw Exception("Could not set timer");
}


Uint32 TimerTask::StaticCallback(Uint32 interval, void* param)
{
	TimerTask* task = (TimerTask*)param;
	assert(task != 0);
	return task->callback();
}


void TimerTask::Cancel()
{
	if (id != 0)
		SDL_RemoveTimer(id);
	id = 0;
}

} // namespace SDL
