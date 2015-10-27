
#ifndef WINDOW_H
#define WINDOW_H

#include "SDLpp.h"
#include "Surface.h"
#include "Event.h"
#include "Cursor.h"
#include <string>


namespace SDL
{
	const int NumUserEvents = SDL_NUMEVENTS - SDL_USEREVENT;
	
	
	class Window
	{
	private:	
		typedef boost::signal1<void, const KeyboardEvent&> KeyEvent_t;
		typedef boost::signal1<void, const ActiveEvent&> ActiveEvent_t;
		typedef boost::signal1<void, const MouseMotionEvent&> MouseMotionEvent_t;
		typedef boost::signal1<void, const MouseButtonEvent&> MouseButtonEvent_t;
		typedef boost::signal1<void, const ResizeEvent&> ResizeEvent_t;
		typedef boost::signal1<void, const SystemEvent&> SystemEvent_t;
		typedef boost::signal1<void, const JoystickAxisEvent&> JoystickAxisEvent_t;
		typedef boost::signal1<void, const JoystickBallEvent&> JoystickBallEvent_t;
		typedef boost::signal1<void, const JoystickHatEvent&> JoystickHatEvent_t;
		typedef boost::signal1<void, const JoystickButtonEvent&> JoystickButtonEvent_t;
		typedef boost::signal1<void, const UserEvent&> UserEvent_t;
		typedef boost::signal1<void, const QuitEvent&> QuitEvent_t;

		Window();
		Window(const Window& window);
		Window& operator= (const Window& window);

	public:
		/// <summary>
		/// Set up a video mode with the specified width, height and bits-per-pixel.
		/// If bpp is 0, it is treated as the current display bits per pixel.
		/// The flags parameter is the same as the flags field of the Surface class.
		/// </summary>
		/// <param name="width">Width of a framebuffer surface</param>
		/// <param name="height">Height of a framebuffer surface</param>
		/// <param name="bpp">Bits per pixel of the framebuffer surface</param>
		/// <param name="flags">OR'd surface flag parameters</param>
		/// <returns>The framebuffer surface</returns>
		static SurfacePtr SetVideoMode(int width, int height, int bpp, boost::uint32_t flags);
		
		/// <summary>
		/// Checks if a specified video mode is okay to use.
		/// </summary>
		/// <param name="width">Width of a framebuffer surface</param>
		/// <param name="height">Height of a framebuffer surface</param>
		/// <param name="bpp">Bits per pixel of the framebuffer surface</param>
		/// <param name="flags">OR'd surface flag parameters</param>
		/// <param name="suggestedBpp">[Out] The suggested BPP to use with the specified flags. SDL can emulate other
		/// bits-per-pixel values, however this will not be as fast as the suggested value</param>
		/// <returns>True if video mode is acceptable, false otherwise</returns>
		static bool IsVideoModeOK(int width, int height, int bpp, boost::uint32_t flags, int& suggestedBpp);
		
		/// <summary>
		/// Checks if a specified video mode is okay to use.
		/// </summary>
		/// <param name="width">Width of a framebuffer surface</param>
		/// <param name="height">Height of a framebuffer surface</param>
		/// <param name="bpp">Bits per pixel of the framebuffer surface</param>
		/// <param name="flags">OR'd surface flag parameters</param>
		/// <returns>True if video mode is acceptable, false otherwise</returns>
		static bool IsVideoModeOK(int width, int height, int bpp, boost::uint32_t flags);

		/// <summary>
		/// Obtain the name of the video driver
		/// </summary>
		/// <returns>The driver name is a simple one word identifier like "x11" or "windib"</returns>
		static std::string GetVideoDriverName();

		/// <summary>
		/// Sets the "gamma function" for the display of each color component.
		/// Gamma controls the brightness/contrast of colors displayed on the screen.
		/// A gamma value of 1.0 is identity (i.e., no adjustment is made).
		/// </summary>
		/// <param name="red">Red value</param>
		/// <param name="blue">Blue value</param>
		/// <param name="green">Green value</param>
		static void SetGamma(float red, float blue, float green);
	
		/// <summary>
		/// Sets the caption of the window
		/// </summary>
		/// <param name="title">Window caption to set</param>
		static void SetCaption(const std::string& title);
		
		/// <summary>
		/// Sets the icon of the window
		/// </summary>
		/// <param name="icon">Name of icon to set</param>
		static void SetIcon(const std::string& icon);

		/// <summary>
		/// Gets the current window caption
		/// </summary>
		/// <returns>Window caption</returns>
		static std::string GetCaption();
		
		/// <summary>
		/// Gets the icon name of the window
		/// </summary>
		/// <returns>Icon name</returns>
		static std::string GetIcon();

		/// <summary>
		/// Iconifies (minimises) the window
		/// </summary>
		static void Iconify();

		/// <summary>
		/// Toggles fullscreen mode
		/// </summary>
		static void ToggleFullscreen();

		/// <summary>
		/// Sets whether input should be captured
		/// </summary>
		/// <param name="grab">True if the input should be grabbed, false otherwise</param>
		static void SetGrabInput(bool grab);
		
		/// <summary>
		/// Gets whether input is captured
		/// </summary>
		/// <returns>True if input is captured, false otherwise</returns>
		static bool GetGrabInput();

		// start event code

		/// <summary>
		/// Polls for any pending events. Events are removed from the event queue.
		/// </summary>
		static void PollEvents();

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
		static void PumpEvents();
		
		/// <summary>
		/// Waits indefinitely for the next available event.
		/// </summary>
		static void WaitForEvent();
		
		/// <summary>
		/// Pushes an event onto the event queue.
		///
		/// The event queue can actually be used as a two way communication channel.
		/// Not only can events be read from the queue, but the user can also push their own events onto it.
		///
    /// Note: Pushing device input events onto the queue doesn't modify the state of the device within SDL.
		/// </summary>
		/// <param name="event">Event to push onto the queue.</param>
		static void PushEvent(const UserEvent& event);

		
		static KeyEvent_t KeyUp, KeyDown;
		static ActiveEvent_t MouseEnter, MouseLeave, Minimize, Restore, InputLost, InputGained;
		static MouseMotionEvent_t MouseMove;
		static MouseButtonEvent_t MouseButtonUp, MouseButtonDown;
		static ResizeEvent_t Resize;
		static SystemEvent_t System;
		static JoystickAxisEvent_t JoystickAxis;
		static JoystickBallEvent_t JoystickBall;
		static JoystickHatEvent_t JoystickHat;
		static JoystickButtonEvent_t JoystickButtonUp, JoystickButtonDown;
		static QuitEvent_t Quit;
		static UserEvent_t User[ NumUserEvents ];

		
		// end event code
		
		// start cursor code
		
		/// <summary>
		/// Get the currently active mouse cursor.
		/// </summary>
		/// <returns>The currently active mouse cursor</returns>
		static Cursor_t GetCursor();
		
		/// <summary>
		/// Sets the currently active mouse cursor.
		/// </summary>
		/// <param name="cursor">Cursor to set</param>
		static void SetCursor(Cursor_t cursor);
		
		/// <summary>
		/// Checks if the mouse cursor is visible.
		/// </summary>
		/// <returns>True if the cursor is visible, false otherwise</returns>
		static bool IsCursorVisible();
		
		/// <summary>
		/// Sets whether the mouse cursor is visible.
		/// </summary>
		/// <param name="visible">Visibility flag</param>
		static void SetCursorVisible(bool visible);
		
		/// <summary>
		/// Shows the cursor (same as SetCursorVisible(true))
		/// </summary>
		static void ShowCursor();
		
		/// <summary>
		/// Hides the cursor (same as SetCursorVisible(false))
		/// </summary>
		static void HideCursor();
		
		/// <summary>
		/// Sets the mouse cursor position in screen coordinates.
		/// </summary>
		/// <param name="x">X position</param>
		/// <param name="y">Y position</param>
		static void SetMousePosition(boost::uint16_t x, boost::uint16_t y);
		
		// end cursor code
	};
}


#endif

