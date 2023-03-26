
#include "SDL/SDLpp.h"
#include "SDL/Init.h"
#include "SDL/Window.h"
#include "SDL/Surface.h"

#include <boost/bind/bind.hpp>

#include "Scene.h"
#include "Sphere.h"
#include "Cube.h"
#include "Triangle.h"


#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2.lib")

using namespace SDL;
using namespace boost::placeholders;


Sphere* sphere1 = NULL;


void OnKeyUp(const SDL::KeyboardEvent& event)
{
	switch (event.GetKey())
	{
	case SDLK_w:
		sphere1->Centre.X += 20.0f;
		break;
	case SDLK_s:
		sphere1->Centre.X -= 20.0f;
		break;
	case SDLK_a:
		sphere1->Centre.Y -= 20.0f;
		break;
	case SDLK_d:
		sphere1->Centre.Y += 20.0f;
		break;
	}
}



void OnQuit(const QuitEvent& event)
{
	exit(0);
}


int main(int argc, char* argv[])
{
	const auto initPtr = SDL::Init::Create();
	auto window = WindowPtr(new Window("RayTracer", 640, 480));

	window->Quit.connect(boost::bind(&OnQuit, _1));

	Scene scene(window, window->GetSurface());


	Plane* plane = new Plane( 0, 1, -0.05f, 250.0f );
	plane->Material.Reflectivity = 0.0f;
	plane->Material.Diffuse = 1.0f;
	plane->Material.Color = Color( 255, 255, 255, 255 );
	scene.AddObject( Scene::ObjectPtr_t( plane ) );

	Sphere* sphere = new Sphere();
	sphere->Radius = 150.0f;
	sphere->Material.Color = SDL::Color( 150, 50, 50, 0 );
	sphere->Material.Diffuse = 0.5f;
	sphere->Material.Specular = 0.5f;
	sphere->Material.Reflectivity = 1.0f;
	scene.AddObject( Scene::ObjectPtr_t( sphere ) );

	sphere = new Sphere();
	sphere1 = sphere;
	sphere->Radius = 100.0f;
	sphere->Centre = Vector3( 100.0f, 250.0f, 100.0f );
	sphere->Material.Color = SDL::Color( 20, 150, 20, 0 );
	sphere->Material.Diffuse = 1.0f;
	sphere->Material.Specular = 1.0f;
	sphere->Material.Reflectivity = 1.0f;
	scene.AddObject( Scene::ObjectPtr_t( sphere ) );

	sphere = new Sphere();
	sphere->Radius = 60.0f;
	sphere->Material.Reflectivity = 1.0f;
	sphere->Material.Specular = 1.0f;
	sphere->Centre = Vector3( 350.0f, -50.0f, 180.0f );
	sphere->Material.Color = SDL::Color( 20, 20, 150, 0 );
	scene.AddObject( Scene::ObjectPtr_t( sphere ) );

	sphere = new Sphere();
	sphere->Radius = 150.0f;
	sphere->Centre = Vector3( -300.0f, 50.0f, 100.0f );
	sphere->Material.Color = SDL::Color( 50, 50, 50, 0 );
	sphere->Material.Diffuse = 1.0f;
	sphere->Material.Specular = 1.0f;
	sphere->Material.Reflectivity = 1.0f;
	scene.AddObject( Scene::ObjectPtr_t( sphere ) );

	PointLight* light = new PointLight();
//	light->Direction = Vector3( -1, 0, 0 );
	light->Position = Vector3( 50.0f, 500.0f, -100.0f );

	scene.AddLight( Scene::LightPtr_t( light ) );

	scene.Render();
	window->UpdateSurface();

	window->KeyUp.connect( boost::bind( &OnKeyUp, _1 ) );

	while(true)
	{
		window->WaitForEvent();
	}

	return 0;
}


