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
	_rend = &_gameObject->AddComponent<LineRenderer>();
	_rend->debug = true;
	_gun.SetGameObject(_gameObject);
}


void PlayerShoot::Tick()
{
	HandleInputs();
	ShowAim();
	Shoot();
}


void PlayerShoot::HandleInputs()
{
	bool d = _game->KeyHeld(GLFW_KEY_D);
	bool a = _game->KeyHeld(GLFW_KEY_A);
	bool s = _game->KeyHeld(GLFW_KEY_S);
	bool w = _game->KeyHeld(GLFW_KEY_W);

	if (d || a) _aimVector.x = (float)(d - a);
	if (s || w ) _aimVector.y = (float)(s - w);

	
	
	_aimVector = normalize(_aimVector);

	//if (_aimVector.magnitude() == 0.0f) _aimVector.x = 1.0f;

	_wantsToShoot = _game->KeyPressed(GLFW_KEY_F);
}


void PlayerShoot::ShowAim()
{
	float2 pos = _gameObject->GetWorldPos();

	_rend->SetLine(pos, pos + float2(_aimVector.x * 10, _aimVector.y * 10));
}


void PlayerShoot::Shoot()
{
	if (!_wantsToShoot) return;
	_gun.Shoot(_aimVector);
}







