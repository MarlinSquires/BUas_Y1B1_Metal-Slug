#include "precomp.h"

#include "mainScene.h"
#include "sceneManager.h"
#include "sceneFactory.h"



void SceneManager::LoadObject(GameObject* go)
{
	currentScene->LoadObject(go);
}

void SceneManager::UnloadObject(int index)
{
	currentScene->UnloadObject(index);
}

// Loads with debug info
void SceneManager::LoadScene(int sceneID, bool debug)
{
	if (currentScene != nullptr) delete currentScene;
	currentScene = new MainScene(); // Hardcoded to init mainScene, no real system yet
	currentScene->LoadScene();
	currentScene->SetDebug(debug);
	currentScene->Start();
	currentScene->PostStart();
}


void SceneManager::Tick()
{
	currentScene->Tick();
}