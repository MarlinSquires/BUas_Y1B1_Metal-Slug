#pragma once
#include "component.h"

#include "accelMove.h"
#include "utils.h"

class GameObject;

class Rigidbody;
class Health;
class RectCollider;
class Animator;


enum class EnemyState : uint8_t
{
	Idle,
	Normal,
	Panick,
	Sneak,
	KnifeAttack,
	BombAttack,
	Dying
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
	void Start() override;
	void Tick() override;


	Enemy(EnemyType type, GameObject* player) : _type(type), _player(player) {};




private:

	char PlayerDir();
	float PlayerDistance();
	void SetDir(face_player facePlayer);

	// State
	void HandleState();

	void IdleTransition();
	void PanickTransition();

	void NormalTransition();
	void SneakTransition();

	void KnifeAttackTransition();
	void BombAttackTransition();

	void DyingTransition();



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
	float _knifeAttackRange = 15.0f;
	float _knifeColOffset = 25.0f;

	float _bombAttackRangeMin = 30.0f;
	float _bombAttackRangeMax = 80.0f;

	// State
	EnemyState _state = EnemyState::Idle;
	bool _blockTransition = false; // Block state transitions (except for enter dying) when performing certain actions

	EnemyType _type;



	// Components
	Rigidbody* _rb = nullptr;
	Animator* _anim = nullptr;
	Health* _hp = nullptr;
	RectCollider* _col = nullptr;
	RectCollider* _knifeCol = nullptr;
	AccelMove _move;


	GameObject* _player = nullptr;


};

