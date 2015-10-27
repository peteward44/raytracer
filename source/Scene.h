
#ifndef RAYTRACER_H
#define RAYTRACER_H


#include "SDL/SDLpp.h"
#include "SDL/Window.h"
#include "SDL/Surface.h"

#include "Object.h"
#include "Vector3.h"
#include "Plane.h"
#include <vector>

#include <boost/shared_ptr.hpp>

#include "Light.h"


class Scene
{
public:
	typedef boost::shared_ptr<Object> ObjectPtr_t;
	typedef boost::shared_ptr<Light> LightPtr_t;

private:
	typedef std::vector< ObjectPtr_t > ObjectContainer_t;
	typedef std::vector< LightPtr_t > LightContainer_t;

	bool shadowson, specularon;

	SDL::SurfacePtr frameBuffer;
	ObjectContainer_t objects;
	LightContainer_t lights;
	std::vector< std::vector< Vector3 > > directionTable;

	void GenerateDirectionTable();
	void RayTrace( const Ray& ray, Vector3& colour, Object*& objecthit, float& objectdist, int recursionDepth = 1 );

	Vector3 CalculateDiffuse( const Material& material, const Ray& pray, const Vector3& lightdirection, const SDL::Color& lightColour, const Vector3& incidentNormal, float mod = 1.0f );
	Vector3 CalculateSpecular( const Material& material, const Ray& pray, const Vector3& lightdirection, const SDL::Color& lightColour, const Vector3& incidentNormal, float mod = 1.0f );

public:
	Scene(SDL::SurfacePtr frameBuffer);

	void OnKeyUp(const SDL::KeyboardEvent& event);
	void Render();

	void AddObject(ObjectPtr_t object);
	void RemoveObject(ObjectPtr_t object);

	void AddLight(LightPtr_t light);
	void RemoveLight(LightPtr_t light);

	inline void SetShadows( bool on ) { shadowson = on; }
	inline void SetSpecular( bool on ) { specularon = on; }

};


#endif

