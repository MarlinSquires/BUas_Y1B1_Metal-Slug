#include "precomp.h"
#include "game.h"
#include "sceneManager.h"
#include "central.h"
#include "animationLibrary.h"
#include "utils.h"



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
    UpdateKeys();
	sceneManager.Tick();
}



void Game::UpdateKeys()
{
    for (int i = 0; i < keycount; i++)
    {
        const uint down = keystate[i] != 0;   // normalise to 0/1
        const uint was = prevKeys[i] != 0;

        pressed[i] = down & ~was & 1;        // down now, not down before
        released[i] = ~down & was & 1;        // down before, not down now
        prevKeys[i] = down;                   // remember for next tick
    }
}