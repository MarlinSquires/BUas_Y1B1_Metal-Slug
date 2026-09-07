#pragma once

class Scene;

class SceneManager
{

public:
	void LoadScene(int sceneID, bool debug);

	void Tick();

	Scene* GetScene() { return currentScene; }; // Return current scene

private:

	Scene* currentScene;


};

