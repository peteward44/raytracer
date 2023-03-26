
#ifndef WINDOW_H
#define WINDOW_H

#include "SDLpp.h"
#include "Surface.h"
#include "Event.h"
#include <string>


namespace SDL
{
	const int NumUserEvents = SDL_LASTEVENT - SDL_USEREVENT;
	
	
	class Window
	{
	private:	
		typedef boost::signals2::signal<void (const KeyboardEvent&)> KeyEvent_t;
		typedef boost::signals2::signal<void (const MouseMotionEvent&)> MouseMotionEvent_t;
		typedef boost::signals2::signal<void (const MouseButtonEvent&)> MouseButtonEvent_t;
		typedef boost::signals2::signal<void (const SystemEvent&)> SystemEvent_t;
		typedef boost::signals2::signal<void (const JoystickAxisEvent&)> JoystickAxisEvent_t;
		typedef boost::signals2::signal<void (const JoystickBallEvent&)> JoystickBallEvent_t;
		typedef boost::signals2::signal<void (const JoystickHatEvent&)> JoystickHatEvent_t;
		typedef boost::signals2::signal<void (const JoystickButtonEvent&)> JoystickButtonEvent_t;
		typedef boost::signals2::signal<void (const UserEvent&)> UserEvent_t;
		typedef boost::signals2::signal<void (const QuitEvent&)> QuitEvent_t;

		SDL_Window* mWindow;
		SurfacePtr mSurface;
		bool mIsFullScreen;

		void CallEvents(SDL_Event* event);

		Window(const Window& window);
		Window& operator= (const Window& window);

	public:
		Window(const std::string& windowCaption, int width, int height);

		SurfacePtr GetSurface() { return mSurface; }

		void UpdateSurface();

		/// <summary>
		/// Toggles fullscreen mode
		/// </summary>
		void ToggleFullscreen();

		// start event code

		/// <summary>
		/// Polls for any pending events. Events are removed from the event queue.
		/// </summary>
		void PollEvents();

		/// <summary>
		/// Pumps the event loop, gathering events from the input devices.
		/// PumpEvents gathers all the pending input information from devices and places it on the event queue.
		/// Without calls to PumpEvents no events would ever be placed on the queue.
		/// Often calls the need for PumpEvents is hidden from the user since PollEvents and WaitForEvent
		/// implicitly call PumpEvents.
		///
		/// However, if you are not polling or waiting for events (e.g. you are filtering them),
		/// then you must call PumpEvents to force an event queue update.
		///
    /// Note: You can only call this function in the thread that set the video mode.
		/// </summary>
		void PumpEvents();
		
		/// <summary>
		/// Waits indefinitely for the next available event.
		/// </summary>
		void WaitForEvent();
		
		/// <summary>
		/// Pushes an event onto the event queue.
		///
		/// The event queue can actually be used as a two way communication channel.
		/// Not only can events be read from the queue, but the user can also push their own events onto it.
		///
    /// Note: Pushing device input events onto the queue doesn't modify the state of the device within SDL.
		/// </summary>
		/// <param name="event">Event to push onto the queue.</param>
		void PushEvent(const UserEvent& event);

		
		KeyEvent_t KeyUp, KeyDown;
		MouseMotionEvent_t MouseMove;
		MouseButtonEvent_t MouseButtonUp, MouseButtonDown;
		SystemEvent_t System;
		JoystickAxisEvent_t JoystickAxis;
		JoystickBallEvent_t JoystickBall;
		JoystickHatEvent_t JoystickHat;
		JoystickButtonEvent_t JoystickButtonUp, JoystickButtonDown;
		QuitEvent_t Quit;
		UserEvent_t User[ NumUserEvents ];

		
		// end event code
		
		/// <summary>
		/// Sets the mouse cursor position in screen coordinates.
		/// </summary>
		/// <param name="x">X position</param>
		/// <param name="y">Y position</param>
		void SetMousePosition(boost::uint16_t x, boost::uint16_t y);
	};

	typedef boost::shared_ptr<Window> WindowPtr;
}


#endif

