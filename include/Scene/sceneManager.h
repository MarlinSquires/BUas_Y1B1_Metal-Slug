#pragma once

class MyScene;
class GameObject;

// Handles scene lifetime, logic, and switching


enum class SceneName
{
	Intro,
	Main
};


class SceneManager
{

public:
	
	// Scene functionality
	void LoadScene(SceneName sceneName, bool debug);

	static void LoadObject(GameObject& go);
	static void UnloadObject(int index);
	

	// Lifetime
	void Tick();

	static bool RanStart();
	static bool RanPostStart();

	static MyScene& GetScene() { return *_currentScene; }; // Return current scene

private:

	static inline MyScene* _currentScene = nullptr;
	SceneName _currentSceneName;


};

