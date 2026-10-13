#include "precomp.h"


#include "central.h"

#include "animationTypes.h"

#include "rigidbody.h"
#include "health.h"
#include "enemy.h"

#include "spriteRenderer.h"
#include "rectRenderer.h"
#include "rectCollider.h"
#include "animator.h"

#include "renderSystem.h"
#include "collisionSystem.h"

#include "sceneManager.h"




void Enemy::Start()
{
	_rb = GetGameObject()->GetComponent<Rigidbody>();
	_hp = &GetGameObject()->AddComponent<Health>(_startHP);
	_col = GetGameObject()->GetComponent<RectCollider>(); // Get rectCol of body

	_knifeCol = &GetGameObject()->AddComponent<RectCollider>(CollisionLayerName::Triggers, float2(20.0f, 20.0f)); // Add rectCol for knife attack
	_knifeCol->SetOffset(_knifeColOffset, 0.0f);
	&GetGameObject()->AddComponent<RectRenderer>(_knifeCol);

	_anim = GetGameObject()->GetComponent<Animator>();
	
	assert(_hp != nullptr && _rb != nullptr);
}

void Enemy::Tick()
{
	HandleState();
}


void Enemy::HandleState()
{
	switch (_state)
	{
		case EnemyState::Idle:

			// Logic
			CheckHP();

			// Transitions


			if (PlayerDistance() < 600.0f) NormalTransition();
			


			break;


		case EnemyState::Normal:

			// Logic
			CheckHP();
			SetDir(face_player::yes);
			_move.Move(*_rb, _xDir, _accel, _accel, _speed, _speed);


			// Transitions
			PanickTransition();
			KnifeAttackTransition();
			BombAttackTransition();



			break;


		case EnemyState::Panick:

			// Logic
			CheckHP();
			SetDir(face_player::yes);
			SetKnifePos();
			_move.Move(*_rb, _xDir, _accel, _accel, _speed, _speed);


			// Transitions
			SneakTransition();
			NormalTransition();


			break;

	

		case EnemyState::Sneak:

			// Logic
			CheckHP();
			SetKnifePos();
			_move.Move(*_rb, _xDir, _accel, _accel, _speed, _speed);

			// Transitions
			NormalTransition();


			break;

		case EnemyState::KnifeAttack:

			// Logic
			CheckHP();
			SetKnifePos();

			// Transitions
			NormalTransition();


			break;

		case EnemyState::BombAttack:
			
			// Logic
			CheckHP();


			// Transitions
			NormalTransition();



			break;

		case EnemyState::Dying: // Final state, cannot be transitioned from

			// Logic

			// Transitions


			break;
	}



}





#pragma region Transitions
void Enemy::IdleTransition()
{
	if (_blockTransition) return;

	_state = EnemyState::Idle;
}

void Enemy::NormalTransition()
{
	if (_blockTransition) return;

	//printf("Entering normal state\n");
	_xDir = PlayerDir();

	_state = EnemyState::Normal;
}

void Enemy::PanickTransition()
{
	if (_blockTransition) return;
	//printf("Entering panick state\n");
	_state = EnemyState::Panick;

}

void Enemy::SneakTransition()
{
	if (_blockTransition) return;
	//printf("Entering sneak state\n");
	_xDir = -PlayerDir();


	_state = EnemyState::Sneak;

}

void Enemy::KnifeAttackTransition()
{
	if (_blockTransition) return;
	//printf("Entering knifeAttack state\n");
	_xDir = PlayerDir();

	float distance = utils::distance(_player->GetWorldPos(), GetGameObject()->GetWorldPos());

	if (distance <= _knifeAttackRange) _state = EnemyState::KnifeAttack;
}

void Enemy::BombAttackTransition()
{
	if (_blockTransition) return;
	//printf("Entering bombAttack state\n");

	_xDir = PlayerDir();

	bool inRange = PlayerDistance() >= _bombAttackRangeMin && PlayerDistance() <= _bombAttackRangeMax;
	if (inRange) _state = EnemyState::KnifeAttack;

}

void Enemy::DyingTransition() // Enemy plays dying animation, holds final frame, and then despawns when offscreen
{
	//printf("Entering dying state\n");
	_rb->active = false;
	_col->active = false;

	_state = EnemyState::Dying;
}
#pragma endregion






void Enemy::SetMoveStats(float accel, float decel, float speed)
{
	_accel = accel;
	_decel = decel;
	_speed = speed;
}


char Enemy::PlayerDir()
{
	return (char)utils::sign((_player->GetWorldPos() - GetGameObject()->GetWorldPos()).x);
}

float Enemy::PlayerDistance()
{
	return utils::distance(_player->GetWorldPos(), GetGameObject()->GetWorldPos());
}

void Enemy::SetDir(face_player facePlayer)
{
	// Default position is facing left
	bool flipped = (PlayerDir() == 1);
	if (!facePlayer) flipped = !flipped;
	_anim->SetFlipped(flipped);
}

void Enemy::SetKnifePos()
{
	_knifeCol->SetOffset(_knifeColOffset * _xDir, 0.0f);
}


void Enemy::CheckHP()
{
	if (_hp->ShouldDie())
	{
		DyingTransition();
		GetGameObject()->MarkForDestruction();
	}
}







