#pragma once


#include "renderSystem.h"
#include "collisionSystem.h"

class GameObject;


// Abstract class
class MyScene
{

public:

	virtual void LoadScene() = 0; // Instantiates all initial game objects
	void Start(); // Calls Start() on all objects
	void PostStart();
	void Tick(); // Calls Tick() on all objects

	void SetDebug(bool debugState);
	void LoadObject(GameObject* go);
	void UnloadObject(int index);

	// Structors
	virtual ~MyScene();

private:

	int _objectCount = 0;
	bool _debug;

	GameObject* _objects[100];
	RenderSystem _renderSystem = RenderSystem();
	CollisionSystem _collisionSystem = CollisionSystem();

};

