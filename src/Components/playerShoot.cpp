#include "precomp.h"
#include "game.h"

#include "playerShoot.h"
#include "central.h"


void PlayerShoot::Start()
{
	_game = Central::game;
}


void PlayerShoot::Tick()
{
	HandleInputs();
}


void PlayerShoot::HandleInputs()
{
	_targetVector.x = _game->IsKeyDown(GLFW_KEY_D) - _game->IsKeyDown(GLFW_KEY_A);
	_targetVector.y = _game->IsKeyDown(GLFW_KEY_S) - _game->IsKeyDown(GLFW_KEY_W);
}

void PlayerShoot::LerpAim()
{
	_aimVector.x = lerp_(_aimVector.x, _targetVector.x, _aimRate);


}










