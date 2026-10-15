#include "precomp.h"

#include "central.h"
#include "utils.h"
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


// Structors

Enemy::Enemy(EnemyType type, GameObject* player) : _type(type), _player(player) 
{
	switch (_type)
	{
	case EnemyType::Basic :
		_sneakChance = 0.1f;
		_scareChance = 0.1f;
		break;

	case EnemyType::Sneaky:
		_sneakChance = 0.3f;
		_scareChance = 0.05f;
		break;


	case EnemyType::Scared:
		_sneakChance = 0.05f;
		_scareChance = 0.3f;
		break;
	}
};



// Lifecycle
void Enemy::Start()
{
	_hp = &GetGameObject()->AddComponent<Health>(_startHP);

	_rb = GetGameObject()->GetComponent<Rigidbody>();
	_col = GetGameObject()->GetComponent<RectCollider>(); // Get rectCol of body

	_knifeCol = &GetGameObject()->AddComponent<RectCollider>(CollisionLayerName::Triggers, float2(20.0f, 20.0f)); // Add rectCol for knife attack
	_knifeCol->SetOffset(_knifeColOffset, 0.0f);
	&GetGameObject()->AddComponent<RectRenderer>(_knifeCol);

	_anim = GetGameObject()->GetComponent<Animator>();
	
	assert(_hp != nullptr && _rb != nullptr);
}

void Enemy::PostStart()
{
	_rend = GetGameObject()->GetComponent<SpriteRenderer>();
	EnterIdle();
}

void Enemy::Tick()
{
	Timers();
	HandleState();
}



#pragma region STATE LOGIC STARTS HERE
void Enemy::HandleState()
{
	switch (_state)
	{
		case EnemyState::Idle:
			IdleBehaviour();
			break;

		case EnemyState::Run:
			RunBehaviour();
			break;

		case EnemyState::Sneak:
			SneakBehaviour();
			break;

		case EnemyState::Scared:
			ScaredBehaviour();
			break;

		case EnemyState::RunAway:
			RunAwayBehaviour();
			break;

		case EnemyState::KnifeAttack:
			KnifeAttackBehaviour();
			break;

		case EnemyState::BombAttack:
			BombAttackBehaviour();
			break;

		case EnemyState::Dying: // Final state, cannot be transitioned from
			break;
	}
}




void Enemy::EnterIdle()
{
	if (debug) printf("Entering idle state\n");
	_state = EnemyState::Idle;
}

void Enemy::IdleBehaviour()
{
	// Transitions
	if (_rend->OffScreen()) return;
	
	RandSneak();
}




void Enemy::EnterRun()
{
	if (debug) printf("Entering normal state\n");

	// Entry changes
	SetMoveStats(_runAccel, _runDecel, _runSpeed);
	_anim->SetClip(1);

	_state = EnemyState::Run;
}

void Enemy::RunBehaviour()
{
	// Logic
	CheckHP();
	SetDir(face_player::yes);
	_mover.Move(*_rb, _xDir, _accel, _accel, _speed, _speed);


	// Transitions
	float d = PlayerDistance();
	//if (d <= _bombAttackRangeMax && d >= _bombAttackRangeMin) EnterBombAttack();

	if (d <= _knifeAttackRange && _knifeCooldownTimer <= 0.0f) EnterKnifeAttack();

	RandScare();
}




void Enemy::EnterSneak()
{
	if (debug) printf("Entering sneak state\n");

	// Entry changes
	_anim->SetClip(2);
	SetMoveStats(_sneakAccel, _sneakDecel, _sneakSpeed);

	_state = EnemyState::Sneak;
}

void Enemy::SneakBehaviour()
{
	// Logic
	CheckHP();
	SetKnifePos();
	SetDir(face_player::no);
	_mover.Move(*_rb, _xDir, _accel, _accel, _speed, _speed);

	RandScare();

	// Transitions

	if (PlayerDistance() <= _knifeAttackRange && _knifeCooldownTimer <= 0.0f) EnterKnifeAttack();

	RandScare();

}




void Enemy::EnterScared()
{
	if (PlayerDistance() > _scareRange) return;
	SetDir(face_player::yes);
	_anim->SetClip(3);

	if (debug) printf("Entering scared state\n");
	_state = EnemyState::Scared;
}

void Enemy::ScaredBehaviour()
{
	// Logic
	CheckHP();
	SetKnifePos();
	_rb->Friction(_decel);

	// Transitions
	if (_anim->Finished()) EnterRunAway();
}


void Enemy::EnterRunAway()
{
	if (debug) printf("Entering runAway state\n");
	SetDir(face_player::no);
	_anim->SetClip(4);
	_timer = _scareDuration;
	_state = EnemyState::RunAway;
}

void Enemy::RunAwayBehaviour()
{
	_mover.Move(*_rb, _xDir, _accel, _accel, _speed, _speed);

	_timer -= Central::dts;
	if (_timer <= 0.0f)
	{
		ExitRunAway();
		RandSneak();
	}
}

void Enemy::ExitRunAway()
{
	_scareCooldownTimer = _scareCooldown;
}




void Enemy::EnterKnifeAttack()
{
	if (debug) printf("Entering knifeAttack state\n");
	_anim->SetClip(5);

	_state = EnemyState::KnifeAttack;
}

void Enemy::KnifeAttackBehaviour()
{
	// Logic
	CheckHP();
	SetKnifePos();
	_rb->Friction(_decel);

	// Transitions
	if (!_anim->Finished()) return;
	ExitKnifeAttack();
	RandSneak();
}

void Enemy::ExitKnifeAttack()
{
	_knifeCooldownTimer = _knifeAttackCooldown;
}




void Enemy::EnterBombAttack()
{
	if (debug) printf("Entering bombAttack state\n");

	SetDir(face_player::yes);

	bool inRange = PlayerDistance() >= _bombAttackRangeMin && PlayerDistance() <= _bombAttackRangeMax;
	if (inRange) _state = EnemyState::KnifeAttack;
}

void Enemy::BombAttackBehaviour()
{
	// Logic
	CheckHP();
	_rb->Friction(_decel);

	// Transitions
	if (_anim->Finished()) RandSneak();
}



void Enemy::EnterDying() // Enemy plays dying animation, holds final frame, and then despawns when offscreen
{
	if (debug) printf("Entering dying state\n");
	_rb->active = false;
	_col->active = false;

	_state = EnemyState::Dying;
}

void Enemy::DyingBehaviour()
{

}







// 50/50 chance of entering normal or sneak
void Enemy::RandSneak()
{
	bool r = utils::flip();

	if (r) EnterRun();
	else EnterSneak();
}

// Has a random chance to enter either normal, sneak or panick every second
void Enemy::RandScare()
{
	if (_secondsCounter <= 0.0f)
	{
		_secondsCounter = 1.0f;

		float weights[2];

		if (_state == EnemyState::Run)
		{
			weights[0] = _scareChance; 
			weights[1] = _sneakChance;
			_cumWeight = weights[0] + weights[1];

			float r = utils::random_range(0.0f, 1.0f);
			if (r < weights[0] && _scareCooldownTimer <= 0.0f) EnterScared();
			else if (r < _cumWeight) EnterSneak();
		}

		else if (_state == EnemyState::Sneak)
		{
			weights[0] = _scareChance; 
			weights[1] = _runChance;
			_cumWeight = weights[0] + weights[1];

			float r = utils::random_range(0.0f, 1.0f);
			if (r < weights[0] && _scareCooldownTimer <= 0.0f) EnterScared();
			else if (r < _cumWeight) EnterRun();
		}
	}
}

#pragma endregion STATE LOGIC ENDS HERE







#pragma region GENERAL LOGIC STARTS HERE


void Enemy::Timers()
{
	_knifeCooldownTimer -= Central::dts;
	_scareCooldownTimer -= Central::dts;
	_secondsCounter -= Central::dts;
}

void Enemy::SetMoveStats(float accel, float decel, float speed)
{
	_accel = accel;
	_decel = decel;
	_speed = speed;
}


char Enemy::PlayerDir()
{
	return utils::sign((_player->GetWorldPos() - GetGameObject()->GetWorldPos()).x);
}

float Enemy::PlayerDistance()
{
	return utils::distance(_player->GetWorldPos(), GetGameObject()->GetWorldPos());
}

void Enemy::SetDir(face_player facePlayer)
{
	_xDir = facePlayer == face_player::yes ? PlayerDir() : -PlayerDir();
	bool flipped = _xDir == 1 ? true : false;
	_anim->SetFlipped(flipped);
	SetKnifePos();
}

void Enemy::SetKnifePos()
{
	_knifeCol->SetOffset(_knifeColOffset * _xDir, 0.0f);
}


void Enemy::CheckHP()
{
	if (_hp->ShouldDie())
	{
		EnterDying();
		GetGameObject()->MarkForDestruction();
	}
}
#pragma endregion GENERAL LOGIC ENDS HERE






