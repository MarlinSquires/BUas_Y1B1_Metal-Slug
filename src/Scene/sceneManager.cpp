#include "precomp.h"

#include "mainScene.h"
#include "sceneManager.h"
#include "sceneFactory.h"
#include "central.h"





// Scene functionality
void SceneManager::LoadScene(int sceneID, bool debug) // Loads with debug info
{
	if (_currentScene != nullptr) delete _currentScene;
	_currentScene = new MainScene(); // Hardcoded to init mainScene, no real system yet
	_currentScene->LoadScene();
	_currentScene->SetDebug(debug);
	_currentScene->Start();
	_currentScene->PostStart();
}

void SceneManager::LoadObject(GameObject& go) {	_currentScene->LoadObject(go); }
void SceneManager::UnloadObject(int index) { _currentScene->UnloadObject(index); }



// Lifecycle
void SceneManager::Tick() {
	
	_currentScene->Tick();

	if (Central::game->KeyPressed(GLFW_KEY_G))
	{
		_currentScene->ToggleDebug();
	}

	if (Central::game->KeyPressed(GLFW_KEY_R))
	{
		LoadScene(0, true);
	}



}



// Getters
bool SceneManager::RanStart() { return _currentScene->RanStart(); }
bool SceneManager::RanPostStart() {	return _currentScene->RanPostStart(); }