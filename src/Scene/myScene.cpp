#include "precomp.h"



#include "gameObject.h"
#include "myScene.h"



MyScene::~MyScene()
{
	for (int i = 0; i < _objectCount; i++)
	{
		delete _objects[i];
	}
}


// Called by gameObject constructor
void MyScene::LoadObject(GameObject& go)
{
	assert(_objectCount < MAX_OBJECTS);
	_objects[_objectCount++] = &go;
	go.index = _objectCount - 1;
}

void MyScene::UnloadObject(int index)
{
	assert(index >= 0 && index < _objectCount);

	delete _objects[index];
	_objects[index] = _objects[--_objectCount];
	_objects[index]->index = index;
	_objects[_objectCount] = nullptr;
}


void MyScene::RemoveObjects()
{
	for (int i = 0; i < _objectCount;)
	{
		if (_objects[i]->PendingDestruction()) UnloadObject(_objects[i]->index);
		else ++i;
	}
}


void MyScene::LoadScene() 
{
	_bulletPool.InstantiateToPool();
};


void MyScene::Start()
{
	for (int i = 0; i < _objectCount; i++)
	{
		_objects[i]->Start();
	}

	_ranStart = true;
}


void MyScene::PostStart()
{
	for (int i = 0; i < _objectCount; i++)
	{
		_objects[i]->PostStart();
	}

	_ranPostStart = true;
}

void MyScene::Tick()
{
	for (int i = 0; i < _objectCount; i++)
	{
		if (_objects[i]->PendingDestruction()) continue;
		_objects[i]->Tick();
	}
	_renderSystem.Render();

	RemoveObjects();
}


void MyScene::SetDebug(bool debugState)
{
	_debug = debugState;

	for (int i = 0; i < _objectCount; i++)
	{
		_objects[i]->debug = _debug;
	}
}





