
#ifndef PLANE_H
#define PLANE_H


#include "Vector3.h"
#include "Object.h"


class Plane : public Object
{
public:
	Vector3 Normal;
	float Distance;
	
	inline explicit Plane( float x = 0, float y = 0, float z = 0, float d = 0)
	 : Normal(x, y, z), Distance(d)
	{
		Normal.Normalize();
	}
	
	
//	inline Plane(const Vector3& point1, const Vector3& point2, const Vector3& point3)
//	{
//	}
	
	
	bool Trace( const Ray& ray, float& distance ) const
	{
		/*
	float d = DOT( m_Plane.N, a_Ray.GetDirection() );
	if (d != 0)
	{
		float dist = -(DOT( m_Plane.N, a_Ray.GetOrigin() ) + m_Plane.D) / d;
		if (dist > 0)
		{
			if (dist < a_Dist) 
			{
				a_Dist = dist;
				return HIT;
			}
		}
	}
	return MISS;
	*/
/*
		float vd = Vector3::Dot( Normal, ray.Direction );
		if ( vd <= 0.0001f && vd >= -0.0001f )
			return false; // ray is parallel to the plane

		float t = -(Vector3::Dot( Normal, ray.Origin ) + Distance) / vd;
		
		if (t < 0.0f)
			return false;

		distance = t;
		return true;
*/

		float t = 	-(Vector3::Dot(Normal, ray.Origin) + Distance) / Vector3::Dot(Normal, ray.Direction );
    if(t<0)
    {
			return false;
    }

		distance = t;
		return true;
	}


	Vector3 GetNormal(const Ray& ray, float distance) const
	{
		return Normal;
	}
};


#endif

