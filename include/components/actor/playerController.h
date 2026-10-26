#pragma once
#include "component.h"
#include "game.h"

class PlayerMove;
class PlayerShoot;
class GameObject;

// Handles inputs, and sends commands to PlayerMove and PlayerShoot, coordinating their states
// Also tracks player lives

enum class PlayerState
{
	Inactive, // No moving or shooting, e.g: when in menu
	Free, // Player can freely move and shoot
	Dead, 
	Respawning // Playing respawn animation
};


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
	TheApp* _game = nullptr;
	//AnimationController _animController;

};

