#pragma once

#include "component.h"
#include "game.h"

class Rigidbody;
class RectCollider;
class Animator;


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
	void PostStart() override;
	void Tick() override;

	const PlayerState GetState() { return _playerState; }


	PlayerMove(Animator* upper, Animator* lower) : _animUpper(upper), _animLower(lower) {};

private:

	void MoveInput();
	void Move();
	void FlipSprite();

	// State machine
	void HandleState();

	void FreeTransition();   // Initial transition into free state
	void JumpTransition();   // Initial transition into jump state
	void CrouchTransition(); // Initial transition into crouch state


	void ChangeState(PlayerState targetState);

	void SetStateStats(float minSpeed, float maxSpeed, float groundAccel, float airAccel, float groundDecel, float airDecel);
	void SetGroundedStats();
	void Timers(); // counts down all timers


	// General
	PlayerState _playerState = PlayerState::Free;
	char _xInput = 0;
	float verticalVel = 0.0f;

	// Buffering / coyote
	float _inputBuffer = 0.5f;
	float _inputTimer = 0.0f;

	float _coyoteTime = 0.5f;
	float _coyoteTimer = 0.0f;

	// Base values - should all be 0.0f
	float _minSpeed = 0.0f;
	float _maxSpeed = 0.0f;
	float _decel = 0.0f;
	float _accel = 0.0f;

	float _groundAccel = 0.0f;
	float _airAccel = 0.0f;
	float _groundDecel = 0.0f;
	float _airDecel = 0.0f;

	// Free state
	float _freeMinSpeed = 20.0f;
	float _freeMaxSpeed = 300.0f;
	float _freeGroundAccel = 450.0f;
	float _freeAirAccel = 450.0f;
	float _freeGroundDecel = 800.0f;
	float _freeAirDecel = 100.0f;

	// Crouching
	bool _wantsToCrouch = false;
	float _crouchMinSpeed = 10.0f;
	float _crouchMaxSpeed = 30.0f;
	float _crouchGroundAccel = 200.0f;
	float _crouchAirAccel = 100.0f;
	float _crouchGroundDecel = 200.0f;
	float _crouchAirDecel = 100.0f;
	
	// Jumping
	bool _wantsToJump = false;
	float _jumpForce = -120.0f;
	float _jumpCooldown = 0.5f;
	float _jumpTimer = 0.0f;
	
	Animator* _animUpper = nullptr;
	Animator* _animLower = nullptr;
	RectCollider* _col = nullptr;
	Rigidbody* _rb = nullptr;
	Game* _game = nullptr;

	int _clipIndex = 0;
};

