#include "precomp.h"
#include "game.h"
#include "sceneManager.h"
#include "spriteFactory.h"
#include "central.h"


using namespace Tmpl8;


SceneManager sceneManager;


bool Game::IsKeyDown(int key)
{
	return Central::keystate[key];
}

void Game::Init()
{
	SpriteFactory::Init();
	sceneManager.LoadScene(0, false);
}


void Game::Tick( float /*dt*/)
{
	screen->Clear(0x000000);

	sceneManager.Tick();
}