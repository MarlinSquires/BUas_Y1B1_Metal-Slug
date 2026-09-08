#include "precomp.h"
#include "game.h"
#include "sceneManager.h"
#include "spriteFactory.h"


using namespace Tmpl8;


SceneManager sceneManager;


void Game::Init()
{
	SpriteFactory::Init();
	sceneManager.LoadScene(0, false);
}


void Game::Tick( float /*dt*/)
{
	sceneManager.Tick();
}


void Game::UpdateKeys()
{
    // Update key states
    pressed = keys & ~held; // keys that are currently down but were not down in the previous tick
    released = ~keys & held; // keys that were down in the previous tick but are not down now
    held = keys; // update prevKeys for the next tick
};