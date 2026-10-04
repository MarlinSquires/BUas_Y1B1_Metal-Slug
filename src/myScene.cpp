#include "precomp.h"



#include "gameObject.h"
#include "myScene.h"



MyScene::~MyScene()
{
	for (int i = 0; i < _objectCount; i++) delete _objects[i];

	delete[] _objects;
}



void MyScene::LoadObject(GameObject* go)
{
	_objects[_objectCount++] = go;
	go->SetIndex(_objectCount - 1);
}

void MyScene::UnloadObject(int index)
{
	_objects[index] = _objects[_objectCount--];
}

void MyScene::LoadScene() 
{
	


};


void MyScene::Start()
{
	for (int i = 0; i < _objectCount; i++)
	{
		_objects[i]->Start();
	}
}

void MyScene::Tick()
{
	for (int i = 0; i < _objectCount; i++)
	{
		_objects[i]->Tick();
	}
	_renderSystem.Render();
}


void MyScene::SetDebug(bool debugState)
{
	_debug = debugState;

	for (int i = 0; i < _objectCount; i++)
	{
		_objects[i]->debug = _debug;
	}
}



