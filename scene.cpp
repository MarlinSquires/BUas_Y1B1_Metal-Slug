#include "precomp.h"

#include "gameObject.h"
#include "scene.h"




void Scene::LoadObject(GameObject* go)
{
	objects[objectCount] = go;

}

void Scene::LoadScene() {};


void Scene::Start()
{
	for (int i = 0; i < objectCount; i++)
	{
		objects[i]->Start();
	}
}

void Scene::Tick()
{
	for (int i = 0; i < objectCount; i++)
	{
		objects[i]->Tick();
	}
}


void Scene::SetDebug(bool debugState)
{
	debug = debugState;

	for (int i = 0; i < objectCount; i++)
	{
		objects[i]->debug = debug;
	}
}



Scene::~Scene()
{
	delete[] objects;
	delete renderSystem;
	delete collisionSystem;
}