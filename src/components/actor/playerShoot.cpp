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
	_rend->debug = true;
	_gun.SetGameObject(GetGameObject());
}


void PlayerShoot::Tick()
{
	HandleInputs();
	ShowAim();
	Shoot();
}


void PlayerShoot::HandleInputs()
{
	_aimVector.x = (float)(_game->KeyHeld(GLFW_KEY_D) - _game->KeyHeld(GLFW_KEY_A));
	_aimVector.y = (float)(_game->KeyHeld(GLFW_KEY_S) - _game->KeyHeld(GLFW_KEY_W));
	_aimVector = normalize(_aimVector);

	if (_aimVector.magnitude() == 0.0f) _aimVector.x = 1.0f;

	_wantsToShoot = _game->KeyPressed(GLFW_KEY_F);
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







