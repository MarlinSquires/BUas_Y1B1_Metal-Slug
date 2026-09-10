#include "precomp.h"
#include "game.h"
#include "sceneManager.h"
#include "spriteFactory.h"
#include "central.h"



using namespace Tmpl8;

SceneManager sceneManager;



void Game::Init()
{
	SpriteFactory::Init();
	sceneManager.LoadScene(0, false); // Hardcoded to init mainScene, no real system yet
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