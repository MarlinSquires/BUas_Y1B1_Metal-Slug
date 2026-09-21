#include "precomp.h"
#include "game.h"
#include "sceneManager.h"
#include "central.h"



using namespace Tmpl8;

SceneManager sceneManager;



void Game::Init()
{
	sceneManager.LoadScene(0, true); // Hardcoded to init mainScene, no real system yet
}


void Game::Tick( float /*dt*/)
{
	sceneManager.Tick();
}


// Inputs
bool Game::IsKeyDown(int key)
{
	return Central::keystate[key];
}