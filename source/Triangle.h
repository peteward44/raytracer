
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Object.h"


class Triangle : public Object
{
private:
public:
	Vector3 A, B, C;

	Triangle();
	
	bool Trace(const Ray& ray, float& distance) const;
	Vector3 GetNormal(const Ray& ray, float distance) const;
	
};


#endif

