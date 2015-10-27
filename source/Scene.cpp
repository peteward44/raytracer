#include "Scene.h"

#include "Ray.h"
#include "SDL/Color.h"
#include "Sphere.h"
#include "Plane.h"
#include "SDL/Window.h"
#include "boost/bind.hpp"


const int RAYTRACE_RECURSION_LIMIT = 6;
const float EPSILON = 0.01f;
const float DISTANCE_LIMIT = 20000.0f;


inline Vector3 ColourToVector( const SDL::Color& colour )
{
	float x = ((float)colour.R) / 255.0f;
	float y = ((float)colour.G) / 255.0f;
	float z = ((float)colour.B) / 255.0f;
	return Vector3( x, y, z );
}


inline SDL::Color VectorToColour( const Vector3& vec )
{
	int red = (int)(vec.X * 255.0f);
	int green = (int)(vec.Y * 255.0f);
	int blue = (int)(vec.Z * 255.0f);
	if (red > 255) red = 255;
	if (green > 255) green = 255;
	if (blue > 255) blue = 255;
	return SDL::Color( red, green, blue );
}


Scene::Scene(SDL::SurfacePtr frameBuffer)
	: frameBuffer(frameBuffer)
{
	shadowson = specularon = true;
	GenerateDirectionTable();

	SDL::Window::KeyUp.connect( boost::bind( &Scene::OnKeyUp, this,  _1 ) );
}


void Scene::GenerateDirectionTable()
{
	directionTable.resize(frameBuffer->GetWidth());

	for(int x=0; x<frameBuffer->GetWidth(); x++)
	{
		directionTable[x].resize(frameBuffer->GetHeight());

		for(int y=0; y<frameBuffer->GetHeight(); y++)
		{
			directionTable[x][y].X = (float)x - (float)(frameBuffer->GetWidth())/2.0f;
			directionTable[x][y].Y = -((float)y - (float)(frameBuffer->GetHeight())/2.0f);
			directionTable[x][y].Z = 10000.0f; // this value is fairly arbitrary and can basically be interpreted as field of view
			directionTable[x][y].Normalize();
		}
	}
}


void Scene::OnKeyUp(const SDL::KeyboardEvent& event)
{
	switch (event.GetKey())
	{
	case SDLK_u:
		Render();
		break;
	case SDLK_q:
		exit(0);
		break;
	}
}


void Scene::AddObject(ObjectPtr_t object)
{
	objects.push_back(object);
}


void Scene::RemoveObject(ObjectPtr_t object)
{
	ObjectContainer_t::iterator it = std::find(objects.begin(), objects.end(), object);
	if (it != objects.end())
		objects.erase(it);
}


void Scene::AddLight(LightPtr_t light)
{
	lights.push_back(light);
}


void Scene::RemoveLight(LightPtr_t light)
{
	LightContainer_t::iterator it = std::find(lights.begin(), lights.end(), light);
	if (it != lights.end())
		lights.erase(it);
}


void Scene::Render()
{
	frameBuffer->Fill(SDL::Color(128, 128, 128));
	frameBuffer->Lock();

	Ray ray;
	ray.Origin.X = 0.0f;
	ray.Origin.Y = 0.0f;
	ray.Origin.Z = -16000.0f;

	// calculate each pixel
  for(int y=0; y<frameBuffer->GetHeight(); y++)
  {
		for(int x=0; x<frameBuffer->GetWidth(); x++)
		{
			Vector3 colourvec;
			Object* object;
			float objectdist;
			ray.Direction = directionTable[x][y];

			RayTrace( ray, colourvec, object, objectdist );

			frameBuffer->PutPixel( x, y, VectorToColour( colourvec ) );
		}
	}

	frameBuffer->Unlock();
	frameBuffer->Flip();
}


Vector3 Scene::CalculateDiffuse( const Material& material, const Ray& pray, const Vector3& lightdirection, const SDL::Color& lightColour, const Vector3& incidentNormal, float mod )
{
	// calculate diffuse colouring
	if ( material.Diffuse > 0.0f )
	{
		float lightCoef = Vector3::Dot( lightdirection, incidentNormal );
		if ( lightCoef > 0.0f )
		{
			float diff = material.Diffuse * lightCoef * mod;
			return ColourToVector( material.Color ) * ColourToVector( lightColour ) * diff;
		}
	}

	return Vector3(0,0,0);
}


Vector3 Scene::CalculateSpecular( const Material& material, const Ray& pray, const Vector3& lightdirection, const SDL::Color& lightColour, const Vector3& incidentNormal, float mod )
{
	// specular
	if ( specularon && material.Specular > 0.0f )
	{
		Vector3 r = lightdirection + incidentNormal * Vector3::Dot( Vector3::Normalize( lightdirection ), incidentNormal ) * (-2.0f);
		float dot = Vector3::Dot( pray.Direction, r );
		if ( dot > 0 )
		{
			float spec = powf( dot, 20 ) * material.Specular * mod;
			// add specular component to ray color
			return ColourToVector( lightColour ) * spec;
		}
	}

	return Vector3(0,0,0);
}


void Scene::RayTrace( const Ray& ray, Vector3& objectcolour, Object*& objecthit, float& objectdist, int recursionDepth )
{
	objecthit = NULL;

	if ( recursionDepth > RAYTRACE_RECURSION_LIMIT )
		return;

	objectdist = 16000.0f + DISTANCE_LIMIT;
	float distance = objectdist;

	ObjectContainer_t::const_iterator it = objects.begin();
	ObjectContainer_t::const_iterator itEnd = objects.end();

	// find the closest object it hit
	for (; it != itEnd; ++it)
	{
		if( (*it)->Trace( ray, distance ) && distance < objectdist )
		{
			objecthit = it->get();
			objectdist = distance;
		}
	}

	
	if ( objecthit != 0 )
	{
		Vector3 intersectionPoint = ray.Origin + ( ray.Direction * objectdist );
		Vector3 normal = objecthit->GetNormal( ray, objectdist );
//		normal.Normalize();
		
		// then calculate the color of the pixel, as according to light sources
		LightContainer_t::const_iterator lightit = lights.begin();
		LightContainer_t::const_iterator lightend = lights.end();

		for (; lightit != lightend; ++lightit )
		{
			switch ( (*lightit)->GetLightType() )
			{
			case LIGHT_DIRECTIONAL:
				{
					const DirectionalLight* light = static_cast< const DirectionalLight* >( lightit->get() );

					objectcolour += CalculateDiffuse( objecthit->Material, ray, Vector3::Normalize( light->Direction ), light->Colour, normal );
					objectcolour += CalculateSpecular( objecthit->Material, ray, Vector3::Normalize( light->Direction ), light->Colour, normal );
				}
				break;
			case LIGHT_POINT:
				{
					const PointLight* light = static_cast< const PointLight* >( lightit->get() );

					Vector3 l = light->Position - intersectionPoint;
					l.Normalize();
					Ray r;
					r.Origin = intersectionPoint + l * EPSILON;
					r.Direction = l;

					it = objects.begin();
					itEnd = objects.end();

					float shade = 1.0f;
					if ( shadowson )
					{
						//for (; it != itEnd; ++it)
						//{
						//	float tdist = 0.0f;
						//	if ( (*it).get() != objecthit && (*it)->Trace( r, tdist ) )
						//	{
						//		shade = 0.0f;
						//		break;
						//	}
						//}
					}

					objectcolour += CalculateDiffuse( objecthit->Material, ray, l, light->Colour, normal, shade );
					objectcolour += CalculateSpecular( objecthit->Material, ray, l, light->Colour, normal, shade );
				}
				break;
			case LIGHT_SPOT:
				break;
			}
		}

		// then reflect the ray off the object
		if ( objecthit->Material.Reflectivity > 0.0f )
		{
			Vector3 reflect = ray.Direction + normal * (-2.0f) * Vector3::Dot( ray.Direction, normal );
			reflect.Normalize();
			Vector3 vcolour;
			float dist;
			Object* object;
			Ray newray;
			newray.Origin = intersectionPoint + reflect * (EPSILON );
			newray.Direction = reflect;

			RayTrace( newray, vcolour, object, dist, recursionDepth+1 );

			objectcolour += vcolour * ColourToVector( objecthit->Material.Color ) * objecthit->Material.Reflectivity;
		}
	}
}

