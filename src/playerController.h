#pragma once
#include "component.h"



class PlayerController : public Component
{
public:
	//void Start() override;
	//void Tick() override;

	PlayerController();

private:

	GameObject* _upper;
	GameObject* _lower;

	//PlayerMove _playerMove;
	//PlayerShoot _playerShoot;
	//AnimationController _animController;

};

