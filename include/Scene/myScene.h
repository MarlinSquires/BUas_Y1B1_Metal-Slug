#pragma once


#include "renderSystem.h"
#include "collisionSystem.h"
#include "bulletPool.h"

class GameObject;


// Abstract class
class MyScene
{
public:

	// Scene functions
	virtual void LoadScene() = 0; // Instantiates all initial game objects
	void LoadObject(GameObject& go);
	void UnloadObject(int index); // Queues object to be deleted

	// LifeCycle
	void Start(); // Calls Start() on all objects
	void PostStart();
	void Tick(); // Calls Tick() on all objects

	// Getters and setters
	bool RanStart() { return _ranStart; }
	bool RanPostStart() { return _ranPostStart; }
	void SetDebug(bool debugState);
	void ToggleDebug() { SetDebug(!_debug); }
	

	// Structors
	virtual ~MyScene();

private:

	void RemoveObjects(); // Deregister will queue objects to be removed, which will only occur at the end of Tick(). Prevents the issue of iterating over junk memory

	
	bool _debug = false;
	bool _ranStart = false;
	bool _ranPostStart = false;


	static const int MAX_OBJECTS = 1024;
	GameObject* _objects[MAX_OBJECTS] = {};
	int _objectCount = 0;

	RenderSystem _renderSystem = RenderSystem();
	CollisionSystem _collisionSystem = CollisionSystem();
	BulletPool _bulletPool = BulletPool();

};

