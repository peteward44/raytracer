
#ifndef LIGHT_H
#define LIGHT_H

#include "Vector3.h"
#include "SDL/Color.h"


enum LIGHT_TYPE
{
	LIGHT_DIRECTIONAL,
	LIGHT_POINT,
	LIGHT_SPOT
};


class Light
{
public:
	Light() : Colour( 255, 255, 255, 0 ) { }
	virtual ~Light()=0;

	SDL::Color Colour;

	virtual LIGHT_TYPE GetLightType() const = 0 {}
};


class DirectionalLight : public Light
{
public:
	DirectionalLight() {}
	~DirectionalLight() {}

	Vector3 Direction;

	virtual LIGHT_TYPE GetLightType() const { return LIGHT_DIRECTIONAL; }
};


class PointLight : public Light
{
public:
	PointLight() {}
	~PointLight() {}

	Vector3 Position;

	virtual LIGHT_TYPE GetLightType() const { return LIGHT_POINT; }
};


class SpotLight : public Light
{
public:
	SpotLight() {}
	~SpotLight() {}

	virtual LIGHT_TYPE GetLightType() const { return LIGHT_SPOT; }
};


#endif

