#pragma once

#include "component.h"
#include "game.h"


class PlayerMove : public Component
{
	void Start() override;
	void Tick() override;

	void Input();

	void Move();

	float2 moveDir;
	float moveSpeed = 0.1;

	Tmpl8::Game* game;
};

