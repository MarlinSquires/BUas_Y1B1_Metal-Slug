#pragma once

#include "component.h"
#include "game.h"

class Rigidbody;
class RectCollider;


enum class PlayerState
{
	Free,
	Jumping,
	Crouching,
	Parachuting,
	Respawning,
	Dead
};



class PlayerMove : public Component
{
public:
	void Start() override;
	void Tick() override;

	const PlayerState GetState() { return _playerState; }

private:

	PlayerState _playerState;

	void MoveInput();
	void Move();

	// State machine
	void HandleState();

	//void FreeStateLogic();
	//void JumpStateLogic();
	//void CrouchStateLogic();

	void FreeTransition();   // Initial transition into free state
	void JumpTransition();   // Initial transition into jump state
	void CrouchTransition(); // Initial transition into crouch state


	void ChangeState(PlayerState targetState);

	void SetStats(float minSpeed, float maxSpeed, float groundAccel, float airAccel);


	// General
	char _horizontalMoveDir;
	float verticalVel = 0.0f;

	// Buffering / coyote
	float _inputBuffer = 0.5f;
	float _inputTimer = 0.0f;

	float _coyoteTime = 0.5f;
	float _coyoteTimer = 0.0f;

	// Base values - should all be 0.0f
	float _minSpeed = 0.0f;
	float _maxSpeed = 0.0f;
	float _groundAccel = 0.0f;
	float _airAccel = 0.0f;

	// Free state
	float _freeMinSpeed = 20.0f;
	float _freeMaxSpeed = 50.0f;
	float _freeGroundAccel = 250.0f;
	float _freeAirAccel = 10.0f;
	
	// Jumping
	bool _wantsToJump = false;
	float _jumpForce = -120.0f;
	
	// Crouching
	bool _wantsToCrouch = false;
	float _crouchMinSpeed = 10.0f;
	float _crouchMaxSpeed = 30.0f;
	float _crouchGroundAccel = 20.0f;
	float _crouchAirAccel = 10.0f;
	

	RectCollider* _col = nullptr;
	Rigidbody* _rb = nullptr;
	Tmpl8::Game* _game = nullptr;
};

