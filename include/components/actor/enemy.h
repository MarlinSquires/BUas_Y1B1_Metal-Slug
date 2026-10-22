#pragma once
#include "component.h"

#include "accelMove.h"
#include "utils.h"

class GameObject;

class SpriteRenderer;
class Rigidbody;
class Health;
class RectCollider;
class RectRenderer;
class Animator;


enum class EnemyState : uint8_t
{
	Idle,
	Run,
	Sneak,
	Scared,
	RunAway,	
	KnifeAttack,
	BombAttack,
	Dead
};

enum class EnemyType : uint8_t
{
	Basic, 
	Scared,
	Sneaky
};


using face_player = utils::bool_value<struct face_player_tag>;

class Enemy : public Component
{
public:

	// Lifecycle
	void Start() override;
	void PostStart() override;
	void Tick() override;

	// Structors
	Enemy(EnemyType type, GameObject* player);

private:


	// How do we handle states?
	// Each state holds an Enter and Logic func, as well as an optional Exit func. 
	// The Logic func holds all state behaviour, as well as the conditions for transitioning to other states
	// When a condition is fulfilled, it calls Exit on its own state, and then Enter on the target state

	// How do I handle random state swapping?
	// Certain states (Normal, sneak, panick) will recieve a random timer that counts down. 
	// When it hits 0, it will transition to one of the other 3 states based on a weighted pool


	char PlayerDir();
	float PlayerDistance();
	void SetDir(face_player facePlayer);

	// STATE -------------------------------------------------------------------------
	void HandleState();

	void EnterIdle();
	void IdleBehaviour();

	void EnterRun();
	void RunBehaviour();

	void EnterSneak();
	void SneakBehaviour();
	void ExitSneak();


	void EnterScared();
	void ScaredBehaviour();

	void EnterRunAway();
	void RunAwayBehaviour();
	void ExitRunAway();


	void EnterKnifeAttack();
	void KnifeAttackBehaviour();
	void ExitKnifeAttack();

	void EnterBombAttack();
	void BombAttackBehaviour();


	void EnterDead();
	void DeadBehaviour();


	void RandSneak(); // Randomly picks between Normal and Sneak states to enter

	void RandScare();
	void Timers();



	void CheckHP();
	void SetKnifePos();
	void SetMoveStats(float accel, float decel, float speed);


	// Move stats
	char _xDir = 0;

	float _accel = 0.0f;
	float _decel = 0.0f;
	float _speed = 0.0f;

	float _runAccel = 100.0f;
	float _runDecel = 600.0f;
	float _runSpeed = 50.0f;

	float _sneakAccel = 100.0f;
	float _sneakDecel = 600.0f;
	float _sneakSpeed = 20.0f;


	// Combat stats
	int _startHP = 1;

	// Panick stats
	float _scareRange = 300.0f;
	float _scareDuration = 4.0f; // Amount of time spent running away
	float _scareCooldown = 3.0f;
	
	// Knife stats
	float _knifeAttackRange = 15.0f;
	float _knifeColOffset = 25.0f;
	float _knifeAttackCooldown = 0.2f;

	// Bomb stats
	float _bombAttackRangeMin = 30.0f;
	float _bombAttackRangeMax = 80.0f;


	// Timer
	float _secondsCounter = 0.0f;
	float _knifeCooldownTimer = 0.0f;
	float _scareCooldownTimer = 0.0f;
	float _timer = 0.0f;

	// State randomization
	float _runChance; // chance of returning to normal per second
	float _sneakChance; // Chance of sneaking per second
	float _scareChance; // Chance of panicking per second of being within the panick range
	float _cumWeight = 0.0f;



	// State
	EnemyState _state;

	EnemyType _type;



	// Components
	SpriteRenderer* _rend = nullptr;
	Rigidbody* _rb = nullptr;
	Animator* _anim = nullptr;
	Health* _hp = nullptr;
	RectCollider* _col = nullptr;
	RectRenderer* _rectRend = nullptr;
	RectCollider* _knifeCol = nullptr;
	AccelMove _mover;


	GameObject* _player = nullptr;


};

