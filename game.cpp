#include "precomp.h"
#include "game.h"
#include "sceneManager.h"


using namespace Tmpl8;


SceneManager sceneManager;


void Game::Init()
{
	sceneManager.LoadScene(0, false);
}


void Game::Tick( float /*dt*/)
{
	sceneManager.Tick();
}