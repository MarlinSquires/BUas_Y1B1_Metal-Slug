#include "precomp.h"

#include "playerMove.h"
#include "central.h"
#include "rectCollider.h"
#include "rigidbody.h"
#include "animator.h"




void PlayerMove::Start()
{
	_game = Central::game;
	_rb = gameObject->GetComponent<Rigidbody>();
	_col = gameObject->GetComponent<RectCollider>();
	
}

void PlayerMove::PostStart()
{
	RunTransition();
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
		case PlayerState::Idle:
			MoveInput();
			SetGroundedStats();
			FlipSprite();


			if (_xInput != 0) RunTransition();
			if (_wantsToJump && _rb->Grounded() && _jumpTimer <= 0.0f) JumpTransition();
			if (_wantsToCrouch) CrouchTransition();

			break;

		case PlayerState::Running: // Transitions into jump, crouch, dead
			
			// Logic
			MoveInput();
			SetGroundedStats();
			Move();
			FlipSprite();

			// Handle run-idle sprites
			/*if (_rb->velocity.x == 0)
			{
				_animLower->SetClip(0);
				_animUpper->SetClip(0);
			}
			else
			{
				_animLower->SetClip(1);
				_animUpper->SetClip(1);

			}*/

			// Transitions
			if (_rb->velocity.x == 0.0f) IdleTransition();
			if (_wantsToJump && _rb->Grounded() && _jumpTimer <= 0.0f) JumpTransition();
			if (_wantsToCrouch) CrouchTransition();

			break;

		case PlayerState::Jumping: // Transitions into free, dead
			
			// Logic
			MoveInput();
			SetGroundedStats();
			Move();
			FlipSprite();
			
			// Transitions
			if (_rb->Grounded()) RunTransition();
			break;

		case PlayerState::Crouching: // Transitions into free, jump, dead
			
			// Logic
			MoveInput();
			SetGroundedStats();
			Move();
			FlipSprite();

			// Transitions
			if (_wantsToCrouch) RunTransition();

			break;

		case PlayerState::Dead: // Transitions back into free state


			break;
	}
}
void PlayerMove::IdleTransition()
{
	printf("Entering / exiting idle state!\n");

	_animLower->SetClip(0);
	_animUpper->SetClip(0);

	_col->SetOffset(1.0f, 1.0f);
	_col->SetScale(1.0f, 1.0f);

	ChangeState(PlayerState::Idle);
}



void PlayerMove::RunTransition()
{
	printf("Entering / exiting run state!\n");

	_animLower->SetClip(1);
	_animUpper->SetClip(1);

	_col->SetOffset(1.0f, 1.0f);
	_col->SetScale(1.0f, 1.0f);

	SetStateStats(_freeMinSpeed, _freeMaxSpeed, _freeGroundAccel, _freeAirAccel, _freeGroundDecel, _freeAirDecel);
	ChangeState(PlayerState::Running);
}


void PlayerMove::JumpTransition()
{
	printf("Entering / exiting jump state!\n");

	_jumpTimer = _jumpCooldown;


	_animLower->SetClip(1);
	_animUpper->SetClip(1);

	_col->SetOffset(1.0f, 1.0f);
	_col->SetScale(1.0f, 1.0f);

	_rb->AddForce(float2(0.0f, _jumpForce));
	ChangeState(PlayerState::Jumping);
}

void PlayerMove::CrouchTransition()
{
	printf("Entering / exiting crouch state!\n");

	_animLower->SetClip(2);
	_animUpper->SetClip(2);

	_col->SetOffset(0, _col->GetSize().y / 2);
	_col->SetScale(1.0f, 0.5f);

	SetStateStats(_crouchMinSpeed, _crouchMaxSpeed, _crouchGroundAccel, _crouchAirAccel, _crouchGroundDecel, _crouchAirDecel);
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


void PlayerMove::FlipSprite()
{
	if (_xInput == 0) return;
	if (_xInput > 0)
	{
		_animLower->SetFlipped(false);
		_animUpper->SetFlipped(false);
	}
	else
	{
		_animLower->SetFlipped(true);
		_animUpper->SetFlipped(true);
	}
}