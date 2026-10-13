#include "precomp.h"
#include "game.h"

#include "playerShoot.h"
#include "renderers/lineRenderer.h"
#include "central.h"
#include "bulletPool.h"
#include "guns/gun.h"


void PlayerShoot::Start()
{
	_game = Central::game;
	_rend = &GetGameObject()->AddComponent<LineRenderer>();
	_gun.SetGameObject(GetGameObject());
}


void PlayerShoot::Tick()
{
	HandleInputs();
	LerpAim();
	ShowAim();
	Shoot();
}


void PlayerShoot::HandleInputs()
{
	_targetVector.x = (float)(_game->KeyHeld(GLFW_KEY_D) - _game->KeyHeld(GLFW_KEY_A));
	_targetVector.y = (float)(_game->KeyHeld(GLFW_KEY_S) - _game->KeyHeld(GLFW_KEY_W));
	//_targetVector = normalize(_targetVector);

	_wantsToShoot = _game->KeyPressed(GLFW_KEY_F);
}

void PlayerShoot::LerpAim()
{
	_aimVector = lerp(_aimVector, _targetVector, (_aimRate * Central::dts));
	_aimVector = normalize(_aimVector);
}

void PlayerShoot::ShowAim()
{
	float2 pos = GetGameObject()->GetWorldPos();

	_rend->SetLine(pos, pos + float2(_aimVector.x * 10, _aimVector.y * 10));
}


void PlayerShoot::Shoot()
{
	if (!_wantsToShoot) return;
	_gun.Shoot(_aimVector);
}







