
#ifndef MESH_H
#define MESH_H

#include "Object.h"


class Mesh : public Object
{
private:
public:
	Mesh();
	
	bool Trace(const Ray& ray, float& distance) const;
	Vector3 GetNormal(const Ray& ray, float distance) const;
	
};


#endif

