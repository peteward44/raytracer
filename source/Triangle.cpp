

#include "Triangle.h"


Triangle::Triangle()
{
}


bool Triangle::Trace(const Ray& ray, float& distance) const
{
	Vector3 edge1 = B - A;
	Vector3 edge2 = C - A;
	Vector3 pvec = Vector3::Cross(ray.Direction, edge2);

	float det = Vector3::Dot(edge1, pvec);

	if(det > -0.000001f && det < 0.000001f)
	{
		return false;
	}
	
	float invDet = 1.0f/det;

	Vector3 tvec = ray.Origin - A;

	float u = Vector3::Dot(tvec, pvec) * invDet;
	if(u < 0.0f || u > 1.0f)
	{
		return false;
	}

	Vector3 qvec = Vector3::Cross(tvec, edge1);

	float v = Vector3::Dot(ray.Direction, qvec) * invDet;
	if(v < 0.0f || (u + v) > 1.0f)
	{
		return false;
	}

	distance = Vector3::Dot(edge2, qvec) * invDet;
	if(distance < 0.0f)
	{
		return false;
	}

	return true;
}


Vector3 Triangle::GetNormal(const Ray& ray, float distance) const
{
	return Vector3::Normalize( Vector3::Cross(B - A, C - A) );
}

