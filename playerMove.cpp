#include "precomp.h"
#include "playerMove.h"
#include "central.h"

#include <iostream>


void PlayerMove::Start()
{
	game = Central::game;
}

void PlayerMove::Tick()
{
	Input();
	Move();
}


void PlayerMove::Input()
{
	int horizontal = game->IsKeyDown(GLFW_KEY_D) - game->IsKeyDown(GLFW_KEY_A);
	int vertical = game->IsKeyDown(GLFW_KEY_S) - game->IsKeyDown(GLFW_KEY_W);

	

	moveDir.x = horizontal;
	moveDir.y = vertical;

	//std::cout << "x: " << moveDir.x << "y: " << moveDir.y << std::endl;
}

void PlayerMove::Move()
{
	gameObject->pos.x += moveDir.x * moveSpeed;
	gameObject->pos.y += moveDir.y * moveSpeed;
}