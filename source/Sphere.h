
#ifndef SPHERE_H
#define SPHERE_H

#include "Object.h"
#include "Vector3.h"


class Sphere : public Object
{
public:
	Vector3 Centre;
	float Radius;

	Sphere();

	virtual bool Trace(const Ray& ray, float& distance) const;
	virtual Vector3 GetNormal(const Ray& ray, float distance) const;
};


#endif

