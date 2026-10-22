#include "precomp.h"

#include "playerMove.h"
#include "central.h"
#include "colliders/rectCollider.h"
#include "rigidbody.h"
#include "animator.h"



// Lifecycle
void PlayerMove::Start()
{
	_game = Central::game;
	_rb = _gameObject->GetComponent<Rigidbody>();
	_col = _gameObject->GetComponent<RectCollider>();
	
}

void PlayerMove::PostStart()
{
	IdleTransition();
}

void PlayerMove::Tick()
{
	HandleState();
	Timers();
}



void PlayerMove::MoveInput()
{
	_xInput = _game->KeyHeld(GLFW_KEY_D) - _game->KeyHeld(GLFW_KEY_A);
	_wantsToJump = _game->KeyPressed(GLFW_KEY_SPACE);
	_wantsToCrouch = _game->KeyPressed(GLFW_KEY_S);
	_wantsToUncrouch = _game->KeyReleased(GLFW_KEY_S);
}


void PlayerMove::HandleState()
{
	switch (_playerState)
	{
		case PlayerMoveState::Idle:
			MoveInput();
			SetGroundedStats();
			FlipSprite();


			if (_xInput != 0) RunTransition();
			if (_wantsToJump && _rb->Grounded() && _jumpTimer <= 0.0f) JumpTransition();
			if (_wantsToCrouch) CrouchTransition();

			break;

		case PlayerMoveState::Running: // Transitions into jump, crouch, dead
			
			// Logic
			MoveInput();
			SetGroundedStats();
			Move();
			FlipSprite();


			// Transitions
			if (abs(_rb->velocity.x) < 0.1f) IdleTransition();
			if (_wantsToJump && _rb->Grounded() && _jumpTimer <= 0.0f) JumpTransition();
			if (_wantsToCrouch) CrouchTransition();

			break;

		case PlayerMoveState::Jumping: // Transitions into free, dead
			
			// Logic
			MoveInput();
			SetGroundedStats();
			Move();
			FlipSprite();
			
			// Transitions
			if (_rb->Grounded()) RunTransition();
			break;

		case PlayerMoveState::Crouching: // Transitions into free, jump, dead
			
			// Logic
			MoveInput();
			SetGroundedStats();
			Move();
			FlipSprite();

			// Transitions
			if (_wantsToUncrouch) RunTransition();

			break;

		case PlayerMoveState::Dead: // Transitions back into free state


			break;
	}
}
void PlayerMove::IdleTransition()
{
	//printf("Entering / exiting idle state!\n");

	_animLower->SetClip(0);
	_animUpper->SetClip(0);

	_col->SetOffset(0.0f, 0.0f);
	_col->SetScale(1.0f, 1.0f);

	ChangeState(PlayerMoveState::Idle);
}



void PlayerMove::RunTransition()
{
	//printf("Entering / exiting run state!\n");

	_animLower->SetClip(1);
	_animUpper->SetClip(1);

	_col->SetOffset(0.0f, 0.0f);
	_col->SetScale(1.0f, 1.0f);

	SetStateStats(_freeMinSpeed, _freeMaxSpeed, _freeGroundAccel, _freeAirAccel, _freeGroundDecel, _freeAirDecel);
	ChangeState(PlayerMoveState::Running);
}


void PlayerMove::JumpTransition()
{
	//printf("Entering / exiting jump state!\n");

	_jumpTimer = _jumpCooldown;


	_animLower->SetClip(1);
	_animUpper->SetClip(1);

	_col->SetOffset(0.0f, 0.0f);
	_col->SetScale(1.0f, 1.0f);

	_rb->velocity.y = _jumpForce;
	//_rb->AddForce(float2(0.0f, _jumpForce));
	ChangeState(PlayerMoveState::Jumping);
}

void PlayerMove::CrouchTransition()
{
	//printf("Entering / exiting crouch state!\n");

	_animLower->SetClip(2);
	_animUpper->SetClip(2);

	_col->SetOffset(0, _col->GetSize().y / 4);
	_col->SetScale(1.0f, 0.5f);

	SetStateStats(_crouchMinSpeed, _crouchMaxSpeed, _crouchGroundAccel, _crouchAirAccel, _crouchGroundDecel, _crouchAirDecel);
	ChangeState(PlayerMoveState::Crouching);
}




void PlayerMove::ChangeState(PlayerMoveState targetState)
{
	_playerState = targetState;
}


void PlayerMove::Move()
{
	_mover.Move(*_rb, _xInput, _accel, _decel, _minSpeed, _maxSpeed);
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