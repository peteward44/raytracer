
#include "Window.h"

using namespace SDL;

Window::Window(const std::string& windowCaption, int width, int height)
: mIsFullScreen(false) {
	mWindow = SDL_CreateWindow(
		windowCaption.c_str(),
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width,
		height,
		SDL_WINDOW_SHOWN
	);
	if (!mWindow) {
		throw Exception("Window could not be created");
	}

	const auto sdlSurface = SDL_GetWindowSurface(mWindow);
	if (!sdlSurface) {
		throw Exception("Screen surface could not be created");
	}
	mSurface = SurfacePtr(new Surface(sdlSurface, true));
}

void Window::UpdateSurface()
{
	SDL_UpdateWindowSurface(mWindow);
}

void Window::ToggleFullscreen()
{
	if (SDL_SetWindowFullscreen(mWindow, mIsFullScreen ? 0 : SDL_WINDOW_FULLSCREEN) == 0) {
		mIsFullScreen = !mIsFullScreen;
	}
}


void Window::CallEvents(SDL_Event* event)
{
	int eventCode = event->type;

	// special case for user-defined events
	if (eventCode >= SDL_USEREVENT && eventCode <= SDL_LASTEVENT-1)
	{
		User[ SDL_USEREVENT - eventCode ](UserEvent(event));
	}
	else
	{
		switch (eventCode)
		{
		case SDL_KEYDOWN:
			KeyDown(KeyboardEvent(event));
			break;

		case SDL_KEYUP:
			KeyUp(KeyboardEvent(event));
			break;

		case SDL_MOUSEMOTION:
			MouseMove(MouseMotionEvent(event));
			break;

		case SDL_MOUSEBUTTONDOWN:
			MouseButtonDown(MouseButtonEvent(event));
			break;

		case SDL_MOUSEBUTTONUP:
			MouseButtonUp(MouseButtonEvent(event));
			break;

		case SDL_JOYAXISMOTION:
			JoystickAxis(JoystickAxisEvent(event));
			break;

		case SDL_JOYBALLMOTION:
			JoystickBall(JoystickBallEvent(event));
			break;

		case SDL_JOYHATMOTION:
			JoystickHat(JoystickHatEvent(event));
			break;

		case SDL_JOYBUTTONDOWN:
			JoystickButtonDown(JoystickButtonEvent(event));
			break;

		case SDL_JOYBUTTONUP:
			JoystickButtonUp(JoystickButtonEvent(event));
			break;

		case SDL_SYSWMEVENT:
			System(SystemEvent(event));
			break;

		case SDL_QUIT:
			Quit(QuitEvent(event));
			break;

		default:
			break;
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


void Window::SetMousePosition(boost::uint16_t x, boost::uint16_t y)
{
	SDL_WarpMouseInWindow(mWindow, x, y);
}

