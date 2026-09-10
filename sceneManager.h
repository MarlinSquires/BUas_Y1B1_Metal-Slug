#pragma once

class MyScene;
class GameObject;

class SceneManager
{

public:
	static void LoadObject(GameObject* go);
	void LoadScene(int sceneID, bool debug);

	void Tick();

	MyScene* GetScene() { return currentScene; }; // Return current scene

private:

	static inline MyScene* currentScene = nullptr;


};

