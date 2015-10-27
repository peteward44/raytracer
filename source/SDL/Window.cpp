
#include "Window.h"

using namespace SDL;


Window::KeyEvent_t Window::KeyDown;
Window::KeyEvent_t Window::KeyUp;
Window::ActiveEvent_t Window::MouseEnter;
Window::ActiveEvent_t Window::MouseLeave;
Window::ActiveEvent_t Window::Minimize;
Window::ActiveEvent_t Window::Restore;
Window::ActiveEvent_t Window::InputGained;
Window::ActiveEvent_t Window::InputLost;
Window::MouseMotionEvent_t Window::MouseMove;
Window::MouseButtonEvent_t Window::MouseButtonUp;
Window::MouseButtonEvent_t Window::MouseButtonDown;
Window::ResizeEvent_t Window::Resize;
Window::SystemEvent_t Window::System;
Window::JoystickAxisEvent_t Window::JoystickAxis;
Window::JoystickBallEvent_t Window::JoystickBall;
Window::JoystickHatEvent_t Window::JoystickHat;
Window::JoystickButtonEvent_t Window::JoystickButtonUp;
Window::JoystickButtonEvent_t Window::JoystickButtonDown;
Window::UserEvent_t Window::User[ NumUserEvents ];
Window::QuitEvent_t Window::Quit;


SurfacePtr Window::SetVideoMode(int width, int height, int bpp, boost::uint32_t flags)
{
	SDL_Surface* surface = SDL_SetVideoMode(width, height, bpp, flags);
	if (surface == 0)
		throw Exception("Could not set video mode");
	return SurfacePtr(new Surface(surface, false));
}


bool Window::IsVideoModeOK(int width, int height, int bpp, boost::uint32_t flags, int& suggestedBpp)
{
	suggestedBpp = SDL_VideoModeOK(width, height, bpp, flags);
	return suggestedBpp != 0;
}


bool Window::IsVideoModeOK(int width, int height, int bpp, boost::uint32_t flags)
{
	int suggestedBpp;
	return IsVideoModeOK(width, height, bpp, flags, suggestedBpp);
}


std::string Window::GetVideoDriverName()
{
	const int videoStringLength = 256;
	char name[ videoStringLength ];
	if (SDL_VideoDriverName(name, videoStringLength) == 0)
		throw Exception("Could not determine video driver name");
	return std::string(name);
}


void Window::SetGamma(float red, float blue, float green)
{
	if (SDL_SetGamma(red, blue, green) == -1)
		throw Exception("Gamma could not be set or is unsupported");
}


void Window::SetCaption(const std::string& caption)
{
	SDL_WM_SetCaption(caption.c_str(), 0);
}


void Window::SetIcon(const std::string& icon)
{
	SDL_WM_SetCaption(0, icon.c_str());
}


std::string Window::GetCaption()
{
	char* title;
	SDL_WM_GetCaption(&title, 0);
	return std::string(title);
}


std::string Window::GetIcon()
{
	char* icon;
	SDL_WM_GetCaption(0, &icon);
	return std::string(icon);
}


void Window::Iconify()
{
	SDL_WM_IconifyWindow();
}


void Window::ToggleFullscreen()
{
	SDL_WM_ToggleFullScreen(SDL_GetVideoSurface());
}


void Window::SetGrabInput(bool grab)
{
	SDL_WM_GrabInput(grab ? SDL_GRAB_ON : SDL_GRAB_OFF);
}


bool Window::GetGrabInput()
{
	return SDL_WM_GrabInput(SDL_GRAB_QUERY) == SDL_GRAB_ON;
}


namespace
{
	void CallEvents(SDL_Event* event)
	{
		int eventCode = event->type;

		// special case for user-defined events
		if (eventCode >= SDL_USEREVENT && eventCode <= SDL_NUMEVENTS-1)
		{
			Window::User[ SDL_USEREVENT - eventCode ](UserEvent(event));
		}
		else
		{
			switch (eventCode)
			{
			case SDL_ACTIVEEVENT:

				switch (event->active.state)
				{
				case SDL_APPMOUSEFOCUS:
					if (event->active.gain == 1)
						Window::MouseEnter(ActiveEvent(event));
					else
						Window::MouseLeave(ActiveEvent(event));
					break;

				case SDL_APPACTIVE:
					if (event->active.gain == 1)
						Window::Restore(ActiveEvent(event));
					else
						Window::Minimize(ActiveEvent(event));
					break;

				case SDL_APPINPUTFOCUS:
					if (event->active.gain == 1)
						Window::InputGained(ActiveEvent(event));
					else
						Window::InputLost(ActiveEvent(event));
					break;
				}

			case SDL_KEYDOWN:
				Window::KeyDown(KeyboardEvent(event));
				break;

			case SDL_KEYUP:
				Window::KeyUp(KeyboardEvent(event));
				break;

			case SDL_MOUSEMOTION:
				Window::MouseMove(MouseMotionEvent(event));
				break;

			case SDL_MOUSEBUTTONDOWN:
				Window::MouseButtonDown(MouseButtonEvent(event));
				break;

			case SDL_MOUSEBUTTONUP:
				Window::MouseButtonUp(MouseButtonEvent(event));
				break;

			case SDL_JOYAXISMOTION:
				Window::JoystickAxis(JoystickAxisEvent(event));
				break;

			case SDL_JOYBALLMOTION:
				Window::JoystickBall(JoystickBallEvent(event));
				break;

			case SDL_JOYHATMOTION:
				Window::JoystickHat(JoystickHatEvent(event));
				break;

			case SDL_JOYBUTTONDOWN:
				Window::JoystickButtonDown(JoystickButtonEvent(event));
				break;

			case SDL_JOYBUTTONUP:
				Window::JoystickButtonUp(JoystickButtonEvent(event));
				break;

			case SDL_SYSWMEVENT:
				Window::System(SystemEvent(event));
				break;

			case SDL_VIDEORESIZE:
				Window::Resize(ResizeEvent(event));
				break;

			case SDL_QUIT:
				Window::Quit(QuitEvent(event));
				break;

			default:
				break;
			}
		}
	}
}


void Window::PollEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event) != 0)
		CallEvents(&event);
}


void Window::PumpEvents()
{
	SDL_PumpEvents();
}


void Window::WaitForEvent()
{
	SDL_Event event;
	if (SDL_WaitEvent(&event) == 0)
		throw EventException();
	CallEvents(&event);
}


void Window::PushEvent(const UserEvent& event)
{
	SDL_Event sdlEvent;

	sdlEvent.type = event.GetType();
	sdlEvent.user.code = event.GetCode();
	sdlEvent.user.data1 = event.GetData1();
	sdlEvent.user.data2 = event.GetData2();

	if (SDL_PushEvent(&sdlEvent) == -1)
		throw EventException();
}


Cursor_t Window::GetCursor()
{
	return Cursor_t( new Cursor(SDL_GetCursor()) );
}


void Window::SetCursor(Cursor_t cursor)
{
	SDL_SetCursor( cursor->GetCursor() );
}


bool Window::IsCursorVisible()
{
	return SDL_ShowCursor(SDL_QUERY) ? SDL_ENABLE : SDL_DISABLE;
}


void Window::SetCursorVisible(bool visible)
{
	visible ? ShowCursor() : HideCursor();
}


void Window::ShowCursor()
{
	SDL_ShowCursor(SDL_ENABLE);
}


void Window::HideCursor()
{
	SDL_ShowCursor(SDL_DISABLE);
}


void Window::SetMousePosition(boost::uint16_t x, boost::uint16_t y)
{
	SDL_WarpMouse(x, y);
}

