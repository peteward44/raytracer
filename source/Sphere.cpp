#include "Sphere.h"

#include <cmath>


Sphere::Sphere()
{
}


bool Sphere::Trace(const Ray& ray, float& distance) const
{
	
	Vector3 rayToSphereCenter = Centre - ray.Origin;
	float lengthRTSC2 = rayToSphereCenter.LengthSq();

	float closestApproach = Vector3::Dot(rayToSphereCenter, ray.Direction);
	if (closestApproach < 0.0f) // the intersection is behind the ray
		return false;

	// halfCord2 = the distance squared from the closest approach of the ray to a perpendicular to the ray
	// through the center of the sphere to the place where the ray actually intersects the sphere
	float halfCord2 = (Radius * Radius) - lengthRTSC2 + (closestApproach * closestApproach);

	if(halfCord2 < 0.0f)
		return false; // the ray missed the sphere

	distance = closestApproach - (float)sqrt((float)halfCord2);
	return true;
	
/*
	Vector3 v = ray.Origin - Centre;
	float b = - Vector3::Dot( v, ray.Direction );
	float det = (b*b) - Vector3::Dot( v, v ) + sqrtf( Radius );

	if ( det > 0.0f )
	{
		det = sqrtf( det );
		float i1 = b - det;
		float i2 = b + det;
		if ( i2 > 0 )
		{
			if ( i1 < 0 )
			{

						// inside sphere
						distance = i2;
						return true;
			}
			else
			{
						// hit sphere
						distance = i1;
						return true;
			}
		}
	}
	return false;
*/
	/*
		vector3 v = a_Ray.GetOrigin() - m_Centre;
	float b = -DOT( v, a_Ray.GetDirection() );
	float det = (b * b) - DOT( v, v ) + m_SqRadius;
	int retval = MISS;
	if (det > 0)
	{
		det = sqrtf( det );
		float i1 = b - det;
		float i2 = b + det;
		if (i2 > 0)
		{
			if (i1 < 0) 
			{
				if (i2 < a_Dist) 
				{
					a_Dist = i2;
					retval = INPRIM;
				}
			}
			else
			{
				if (i1 < a_Dist)
				{
					a_Dist = i1;
					retval = HIT;
				}
			}
		}
	}
	return retval;
	*/
}


Vector3 Sphere::GetNormal(const Ray& ray, float distance) const
{
  Vector3 intersection;

  // intersection between the sphere and the ray. 
  intersection.X = ray.Origin.X + distance * ray.Direction.X;
  intersection.Y = ray.Origin.Y + distance * ray.Direction.Y;
  intersection.Z = ray.Origin.Z + distance * ray.Direction.Z;

  Vector3 normal;

  // calculate the normal of the sphere at the point of interesction
  float oneOverRadius = 1.0f/Radius;

  normal.X = (intersection.X - Centre.X) * oneOverRadius;
  normal.Y = (intersection.Y - Centre.Y) * oneOverRadius;
  normal.Z = (intersection.Z - Centre.Z) * oneOverRadius;

	return Vector3::Normalize(normal);
}


