#include "precomp.h"
#include "game.h"
#include "sceneManager.h"
#include "spriteFactory.h"
#include "central.h"
#include "gridSpawner.h"


using namespace Tmpl8;

SceneManager sceneManager;
GridSpawner* gridSpawner = new GridSpawner("data/level1.tmj");


bool Game::IsKeyDown(int key)
{
	return Central::keystate[key];
}

void Game::Init()
{
	
	SpriteFactory::Init();
	sceneManager.LoadScene(0, false); // Hardcoded to init mainScene, no real system yet
	gridSpawner->Init();
}


void Game::Tick( float /*dt*/)
{
	screen->Clear(0x000000);
	sceneManager.Tick();
}