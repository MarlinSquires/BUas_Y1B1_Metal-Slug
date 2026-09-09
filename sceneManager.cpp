#include "precomp.h"
#include "scene.h"
#include "sceneManager.h"
#include "sceneFactory.h"
#include "mainScene.h"


void SceneManager::LoadObject(GameObject* go)
{
	currentScene->LoadObject(go);
}

// Loads with debug info
void SceneManager::LoadScene(int sceneID, bool debug)
{
	if (currentScene != nullptr) delete currentScene;
	currentScene = new MainScene(); // Hardcoded to init mainScene, no real system yet
	currentScene->LoadScene();
	currentScene->SetDebug(debug);
	currentScene->Start();
}


void SceneManager::Tick()
{
	currentScene->Tick();
}