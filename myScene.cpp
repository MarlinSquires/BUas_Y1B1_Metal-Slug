#include "precomp.h"

#include "gameObject.h"
#include "myScene.h"
#include "renderSystem.h"



void MyScene::LoadObject(GameObject* go)
{
	objects[objectCount++] = go;
}

void MyScene::LoadScene() {};


void MyScene::Start()
{
	for (int i = 0; i < objectCount; i++)
	{
		objects[i]->Start();
	}
}

void MyScene::Tick()
{
	for (int i = 0; i < objectCount; i++)
	{
		objects[i]->Tick();
	}

	renderSystem->Tick();
}


void MyScene::SetDebug(bool debugState)
{
	debug = debugState;

	for (int i = 0; i < objectCount; i++)
	{
		objects[i]->debug = debug;
	}
}



MyScene::~MyScene()
{
	delete[] objects;
	delete renderSystem;
	delete collisionSystem;
}