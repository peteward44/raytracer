
#ifndef CUBE_H
#define CUBE_H

#include "Object.h"
#include "Vector3.h"

#include <cassert>
#include "SDL/Exception.h"

using namespace SDL;


class Cube : public Object
{
private:


public:
	Vector3 AxisX, AxisY, AxisZ, Centre;
	float ExtentX, ExtentY, ExtentZ;
	
	
	Cube();
	Cube(const Vector3& centre, const Vector3& lookDirection, const Vector3& upDirection, float extentX, float extentY, float extentZ);

	virtual bool Trace(const Ray& ray, float& distance) const;
	virtual Vector3 GetNormal(const Ray& ray, float distance) const;

	inline float GetExtent(int i) const
	{
		assert(i >= 0 && i <= 2);
	
		switch (i)
		{
		case 0:
			return ExtentX;
		case 1:
			return ExtentY;
		case 2:
			return ExtentZ;
		}

		throw Exception("Argument invalid");
	}
	
	
	inline void SetExtent(int i, float f)
	{
		assert(i >=0 && i <= 2);
		
		switch (i)
		{
		case 0:
			ExtentX = f;
			break;
		case 1:
			ExtentY = f;
			break;
		case 2:
			ExtentZ = f;
			break;
		default:
			throw Exception("Argument invalid");
		}
	}
	
	
	inline Vector3& GetAxis(int i)
	{
		assert(i >= 0 && i <= 2);
		
		switch (i)
		{
		case 0:
			return AxisX;
		case 1:
			return AxisY;
		case 2:
			return AxisZ;
		default:
			throw Exception("Argument invalid");
		}
	}
	
	
	inline const Vector3& GetAxis(int i) const
	{
		assert(i >= 0 && i <= 2);
		
		switch (i)
		{
		case 0:
			return AxisX;
		case 1:
			return AxisY;
		case 2:
			return AxisZ;
		default:
			throw Exception("Argument invalid");
		}
	}
};


#endif

