#pragma once


class GameObject;
class RenderSystem;
class CollisionSystem;

// Abstract class
class MyScene
{

public:

	virtual void LoadScene() = 0; // Instantiates all initial game objects
	void Start(); // Calls Start() on all objects
	void Tick(); // Calls Tick() on all objects

	void SetDebug(bool debugState);
	void LoadObject(GameObject* go);

	// Structors
	virtual ~MyScene();

private:

	int objectCount = 0;
	bool debug;

	GameObject* objects[100];
	RenderSystem* renderSystem;
	CollisionSystem* collisionSystem;

	
};

