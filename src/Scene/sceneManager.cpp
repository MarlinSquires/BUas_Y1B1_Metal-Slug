#include "precomp.h"

#include "mainScene.h"
#include "sceneManager.h"
#include "sceneFactory.h"
#include "central.h"


// Scene functionality
void SceneManager::LoadScene(SceneName sceneName, bool debug) // Loads with debug info
{
	if (_currentScene != nullptr) delete _currentScene;
	_currentSceneName = sceneName;

	if (sceneName == SceneName::Intro)
	{

	}
	else if (sceneName == SceneName::Main)
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
		LoadScene(_currentSceneName, true);
	}



}



// Getters
bool SceneManager::RanStart() { return _currentScene->RanStart(); }
bool SceneManager::RanPostStart() {	return _currentScene->RanPostStart(); }