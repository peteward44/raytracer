
#ifndef EVENT_H
#define EVENT_H

#include "SDLpp.h"
#include <boost/shared_ptr.hpp>


namespace SDL
{
	class Event
	{
	private:
		int type;

	protected:
		Event(SDL_Event* event)
			: type(event->type)
		{}

		Event(int type)
			: type(type)
		{}

	public:
		virtual ~Event()=0;

		inline boost::uint8_t GetType() const
		{ return type; }

	};


	class UnknownEvent : public Event
	{
	private:

	public:
		UnknownEvent(SDL_Event* event)
			: Event(event)
		{}
	};


	class KeyboardEvent : public Event
	{
	private:
		boost::uint8_t state;
		SDL_Scancode scanCode;
		SDL_Keycode key;
		boost::uint16_t modifiers;

	public:
		KeyboardEvent(SDL_Event* event) : Event(event),
			state(event->key.state), scanCode(event->key.keysym.scancode),
			key(event->key.keysym.sym), modifiers(event->key.keysym.mod)
		{}

		inline boost::uint8_t GetState() const
		{ return state; }

		inline SDL_Scancode GetScanCode() const
		{ return scanCode; }

		inline SDL_Keycode GetKey() const
		{ return key; }

		inline boost::uint16_t GetModifiers() const
		{ return modifiers; }
	};


	class MouseMotionEvent : public Event
	{
	private:
		boost::uint8_t state;
		boost::uint16_t x, y;
		boost::int16_t xrel, yrel;

	public:
		MouseMotionEvent(SDL_Event* event) : Event(event),
			state(event->motion.state), x(event->motion.x),
			y(event->motion.y), xrel(event->motion.xrel),
			yrel(event->motion.yrel)
		{}


		inline boost::uint8_t GetState() const
		{ return state; }
		
		inline boost::uint16_t GetX() const
		{ return x; }

		inline boost::uint16_t GetY() const
		{ return y; }

		inline boost::int16_t GetXRelative() const
		{ return xrel; }

		inline boost::int16_t GetYRelative() const
		{ return yrel; }
	};


	class MouseButtonEvent : public Event
	{
	private:
		boost::uint8_t button, state;
		boost::uint16_t x, y;

	public:
		MouseButtonEvent(SDL_Event* event) : Event(event),
			button(event->button.button), state(event->button.state),
			x(event->button.x), y(event->button.y)
		{}

		inline boost::uint8_t GetState() const
		{ return state; }

		inline boost::uint8_t GetButton() const
		{ return button; }

		inline boost::uint16_t GetX() const
		{ return x; }

		inline boost::uint16_t GetY() const
		{ return y; }
	};


	class JoystickAxisEvent : public Event
	{
	private:
		boost::uint8_t which, axis;
		boost::int16_t value;

	public:
		JoystickAxisEvent(SDL_Event* event) : Event(event),
			which(event->jaxis.which), axis(event->jaxis.axis),
			value(event->jaxis.value)
		{}

		inline boost::uint8_t GetWhich() const
		{ return which; }

		inline boost::uint8_t GetAxis() const
		{ return axis; }

		inline boost::int16_t GetValue() const
		{ return value; }
	};


	class JoystickBallEvent : public Event
	{
	private:
		boost::uint8_t which, ball;
		boost::int16_t xrel, yrel;

	public:
		JoystickBallEvent(SDL_Event* event) : Event(event),
			which(event->jball.which), ball(event->jball.ball),
			xrel(event->jball.xrel), yrel(event->jball.yrel)
		{}

		inline boost::uint8_t GetWhich() const
		{ return which; }

		inline boost::uint8_t GetBall() const
		{ return ball; }

		inline boost::int16_t GetXRelative() const
		{ return xrel; }

		inline boost::int16_t GetYRelative() const
		{ return yrel; }
	};


	class JoystickHatEvent : public Event
	{
	private:
		boost::uint8_t which, hat, value;

	public:
		JoystickHatEvent(SDL_Event* event) : Event(event),
			which(event->jhat.which), hat(event->jhat.hat),
			value(event->jhat.value)
		{}

		inline boost::uint8_t GetWhich() const
		{ return which; }

		inline boost::uint8_t GetHat() const
		{ return hat; }

		inline boost::uint8_t GetValue() const
		{ return value; }
	};


	class JoystickButtonEvent : public Event
	{
	private:
		boost::uint8_t which, button, state;

	public:
		JoystickButtonEvent(SDL_Event* event) : Event(event),
			which(event->jbutton.which), button(event->jbutton.button),
			state(event->jbutton.state)
		{}

		inline boost::uint8_t GetWhich() const
		{ return which; }

		inline boost::uint8_t GetButton() const
		{ return button; }

		inline boost::uint8_t GetState() const
		{ return state; }
	};


	class QuitEvent : public Event
	{
	private:

	public:
		QuitEvent(SDL_Event* event) : Event(event)
		{}
	};


	class SystemEvent : public Event
	{
	private:

	public:
		SystemEvent(SDL_Event* event) : Event(event)
		{}
	};


	class UserEvent : public Event
	{
	private:
		boost::uint8_t code;
		void* data1, *data2;

	public:
		UserEvent(SDL_Event* event) : Event(event),
			code(event->user.code),
			data1(event->user.data1), data2(event->user.data2)
		{}

		UserEvent(boost::uint8_t type, boost::uint8_t code, void* data1, void* data2)
			: Event(type), code(code), data1(data1), data2(data2)
		{}

		inline boost::uint8_t GetCode() const
		{ return code; }

		inline void* GetData1() const
		{ return data1; }

		inline void* GetData2() const
		{ return data2; }
	};
}


#endif

