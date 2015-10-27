
#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>
#include <exception>


namespace SDL
{
	class Exception : public std::exception
	{
	private:
		std::string message;
	
	public:
		Exception()
		{}
		virtual ~Exception() throw()
		{}
		
		Exception(const std::string& message)
			: message(message)
		{
		}

		inline std::string GetMessage() const
		{ return message; }
	};


	class NotImplementedException : public Exception
	{
	};


	class EventException : public Exception
	{
	};


	class SurfaceException : public Exception
	{
	public:
		SurfaceException(const std::string& message) : Exception(message)
		{}

		SurfaceException()
		{}
	};


	class SurfaceLockedException : public Exception
	{
	};
	
	
	class SurfaceLostException : public Exception
	{
	};
	
	
	class CDRomException : public Exception
	{
	public:
		CDRomException(const std::string& message) : Exception(message)
		{}

		CDRomException()
		{}
	};
}


#endif
