#include "precomp.h"
#include "game.h"
#include "sceneManager.h"
#include "central.h"
#include "animationLibrary.h"



using namespace Tmpl8;

SceneManager sceneManager;
AnimationLibrary animLib;


void Game::Init()
{
	Central::animLib = &animLib;
	animLib.Init();
	sceneManager.LoadScene(0, true); // Hardcoded to init mainScene, no real system yet
}


void Game::Tick( float /*dt*/)
{
	sceneManager.Tick();
}


void Game::KeyDown(int key)
{
	Central::keystate[key] = true;
}

void Game::KeyUp(int key)
{

	Central::keystate[key] = false;
}

// Inputs
bool Game::IsKeyDown(int key)
{
	return Central::keystate[key];
}