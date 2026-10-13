#pragma once

class MyScene;
class GameObject;

// Handles scene lifetime, logic, and switching

class SceneManager
{

public:
	
	// Scene functionality
	void LoadScene(int sceneID, bool debug);

	static void LoadObject(GameObject& go);
	static void UnloadObject(int index);
	

	// Lifetime
	void Tick();

	static bool RanStart();
	static bool RanPostStart();

	MyScene* GetScene() { return _currentScene; }; // Return current scene

private:

	static inline MyScene* _currentScene = nullptr;


};

