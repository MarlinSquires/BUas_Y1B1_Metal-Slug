#pragma once
#include "component.h"
#include "game.h"

class PlayerMove;
class PlayerShoot;
class GameObject;

// Handles inputs, and sends commands to PlayerMove and PlayerShoot, coordinating their states

class PlayerController : public Component
{
public:
	//void Start() override;
	void Tick() override;

	PlayerController();

private:

	GameObject* _upper = nullptr;
	GameObject* _lower = nullptr;

	PlayerMove* _playerMove = nullptr;
	PlayerShoot* _playerShoot = nullptr;
	Game* _game = nullptr;
	//AnimationController _animController;

};

