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

	// Particles
	static float a = 0; // Angle
	static float accel = 0.000000005f;
	static float jerk = 0.0f;
	for (int i = 0; i < 100; i++)
	{
		float pa = a + 3.6 * i; // Particle angle
		float px = 160 + 100 * cosf(pa * PI / 180); // Convert from radians to degrees
		float py = 120 + 100 * sinf(pa * PI / 180); // Convert from radians to degrees
		screen->Plot((int)(px), (int)(py), 0xFFFFFF);
	}
	jerk += 0.0000000005f;
	accel += jerk;
	a += accel;


}


// Inputs
bool Game::IsKeyDown(int key)
{
	return Central::keystate[key];
}