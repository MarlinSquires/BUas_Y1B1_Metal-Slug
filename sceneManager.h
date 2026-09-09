#pragma once

class Scene;
class GameObject;

class SceneManager
{

public:
	static void LoadObject(GameObject* go);
	void LoadScene(int sceneID, bool debug);

	void Tick();

	Scene* GetScene() { return currentScene; }; // Return current scene

private:

	static inline Scene* currentScene = nullptr;


};

