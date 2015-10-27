
#ifndef OBJECT_H
#define OBJECT_H

#include "Ray.h"
#include "Material.h"


class Object
{
public:
	Object() {}
	virtual ~Object() {}

	Material Material;


	virtual bool Trace(const Ray& ray, float& distance) const=0;
	virtual Vector3 GetNormal(const Ray& ray, float distance) const=0;

};


#endif

