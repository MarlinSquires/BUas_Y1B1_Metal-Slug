#pragma once
#include "game.h"
#include "component.h"


class PlayerMove : public Component
{
	void Start() override;
	void Tick() override;

	void Input();

	void Move();

	float2 moveDir;
	float moveSpeed = 0.1;

	Game* game;
};

