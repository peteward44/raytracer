
#ifndef MATERIAL_H
#define MATERIAL_H

#include "SDL/Color.h"


class Material
{
private:


public:
	Material()
	{
		Diffuse = 0.2f;
		Specular = 0.0f;
		Reflectivity = 0.0f;
	}

	SDL::Color Color;
	float Diffuse, Specular, Reflectivity;

};


#endif

