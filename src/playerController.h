#pragma once
#include "component.h"



class PlayerController : public Component
{
public:
	//void Start() override;
	//void Tick() override;

	PlayerController();

private:

	PlayerMove playerMove;
	PlayerShoot playerShoot;
	AnimationController animController;

};

