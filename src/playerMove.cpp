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
}

void PlayerMove::MoveInput()
{
	_horizontalMoveDir = _game->IsKeyDown(GLFW_KEY_D) - _game->IsKeyDown(GLFW_KEY_A);
	_wantsToJump = _game->IsKeyDown(GLFW_KEY_SPACE);
	_wantsToCrouch = _game->IsKeyDown(GLFW_KEY_LEFT_SHIFT);
}



void PlayerMove::HandleState()
{
	switch (_playerState)
	{
		case PlayerState::Free: // Transitions into jump, crouch, dead
			MoveInput();
			Move();

			if (_wantsToJump && _rb->Grounded()) JumpTransition();
			if (_wantsToCrouch) CrouchTransition();

			break;

		case PlayerState::Jumping: // Transitions into free, dead
			
			MoveInput();
			Move();
			if (_rb->Grounded()) FreeTransition();

	

			break;

		case PlayerState::Crouching: // Transitions into free, jump, dead
			MoveInput();

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
	SetStats(_freeMinSpeed, _freeMaxSpeed, _freeGroundAccel, _freeAirAccel);
	ChangeState(PlayerState::Free);
}


void PlayerMove::JumpTransition()
{
	printf("Entering / exiting jump state!\n");
	_rb->AddForce(float2(0.0f, _jumpForce));
	ChangeState(PlayerState::Jumping);
}

void PlayerMove::CrouchTransition()
{
	printf("Entering / exiting crouch state!\n");
	SetStats(_crouchMinSpeed, _crouchMaxSpeed, _crouchGroundAccel, _crouchAirAccel);
	_col->SetScale(1.0f, 0.5f);
	ChangeState(PlayerState::Crouching);
}




void PlayerMove::ChangeState(PlayerState targetState)
{
	_playerState = targetState;
}


void PlayerMove::Move()
{
	_rb->velocity.x = clamp(_rb->velocity.x, -_maxSpeed, _maxSpeed);
	_rb->AddForce(float2(_horizontalMoveDir * _groundAccel * Central::dts, 0.0f));
}

void PlayerMove::SetStats(float minSpeed, float maxSpeed, float groundAccel, float airAccel)
{
	_minSpeed = minSpeed;
	_maxSpeed = maxSpeed;
	_groundAccel = groundAccel;
	_airAccel = airAccel;
}