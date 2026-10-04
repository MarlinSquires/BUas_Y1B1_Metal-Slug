#include "precomp.h"

#include "playerMove.h"
#include "central.h"
#include "rectCollider.h"
#include "rigidbody.h"




void PlayerMove::Start()
{
	_game = Central::game;
	_rb = gameObject->GetComponent<Rigidbody>();
	_col = gameObject->GetComponent<RectCollider>();
	FreeTransition();
}

void PlayerMove::Tick()
{
	HandleState();
	Timers();
}

void PlayerMove::MoveInput()
{
	_xInput = _game->IsKeyDown(GLFW_KEY_D) - _game->IsKeyDown(GLFW_KEY_A);
	_wantsToJump = _game->IsKeyDown(GLFW_KEY_SPACE);
	_wantsToCrouch = _game->IsKeyDown(GLFW_KEY_LEFT_SHIFT);
}



void PlayerMove::HandleState()
{
	switch (_playerState)
	{
		case PlayerState::Free: // Transitions into jump, crouch, dead
			MoveInput();
			SetGroundedStats();
			Move();
			

			if (_wantsToJump && _rb->Grounded() && _jumpTimer <= 0.0f) JumpTransition();
			if (_wantsToCrouch) CrouchTransition();

			break;

		case PlayerState::Jumping: // Transitions into free, dead
			MoveInput();
			SetGroundedStats();
			Move();
			

			if (_rb->Grounded()) FreeTransition();
			break;

		case PlayerState::Crouching: // Transitions into free, jump, dead
			MoveInput();
			SetGroundedStats();
			Move();

			if (_wantsToCrouch) FreeTransition();

			break;

		case PlayerState::Dead: // Transitions back into free state


			break;
	}
}


void PlayerMove::FreeTransition()
{
	printf("Entering / exiting free state!\n");
	_col->SetScale(1.0f, 1.0f);
	SetStateStats(_freeMinSpeed, _freeMaxSpeed, _freeGroundAccel, _freeAirAccel, _freeGroundDecel, _freeAirDecel);
	ChangeState(PlayerState::Free);
}


void PlayerMove::JumpTransition()
{
	printf("Entering / exiting jump state!\n");
	_jumpTimer = _jumpCooldown;
	_rb->AddForce(float2(0.0f, _jumpForce));
	ChangeState(PlayerState::Jumping);
}

void PlayerMove::CrouchTransition()
{
	printf("Entering / exiting crouch state!\n");
	SetStateStats(_crouchMinSpeed, _crouchMaxSpeed, _crouchGroundAccel, _crouchAirAccel, _crouchGroundDecel, _crouchAirDecel);
	_col->SetScale(1.0f, 0.5f);
	ChangeState(PlayerState::Crouching);
}




void PlayerMove::ChangeState(PlayerState targetState)
{
	_playerState = targetState;
}


void PlayerMove::Move()
{
	float& xVel = _rb->velocity.x;

	if (_xInput != 0 && abs(xVel) < _minSpeed) // Start off at minSpeed
		_rb->velocity.x = _xInput * _minSpeed;
	else if (_xInput != 0)
		_rb->AddForce(float2(_xInput * _accel * Central::dts, 0.0f)); // Accelerate if above minSpeed

	// Decelerate
	else
	{
		if (xVel >= 0)
		{
			_rb->AddForce(float2(-_decel * Central::dts, 0.0f) );
			if (xVel < 0) _rb->velocity.x = 0; // Stops overshoot
		}
		if (xVel < 0)
		{
			_rb->AddForce(float2(_decel * Central::dts, 0.0f));
			if (xVel > 0) _rb->velocity.x = 0;
		}
	}

	_rb->velocity.x = clamp(_rb->velocity.x, -_maxSpeed, _maxSpeed);
}

void PlayerMove::SetStateStats(float minSpeed, float maxSpeed, float groundAccel, float airAccel, float groundDecel, float airDecel)
{
	_minSpeed = minSpeed;
	_maxSpeed = maxSpeed;
	_groundAccel = groundAccel;
	_groundDecel = groundDecel;
	_airAccel = airAccel;
	_airDecel = airDecel;
}

void PlayerMove::SetGroundedStats()
{
	_accel = _rb->Grounded() ? _groundAccel : _airAccel;
	_decel = _rb->Grounded() ? _groundDecel : _airDecel;
}


void PlayerMove::Timers()
{
	_jumpTimer -= Central::dts;
	_inputTimer -= Central::dts;
	_coyoteTimer -= Central::dts;
}