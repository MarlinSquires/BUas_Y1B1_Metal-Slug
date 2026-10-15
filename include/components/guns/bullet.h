#pragma once
#include "component.h"

// Bullets need a spriteRenderer, an animator, a rectCollider, and a rectRenderer


class BulletPool;
class RectCollider;
class Animator;

class Bullet : public Component
{
	friend class BulletPool;

public:

	void Start() override;
	void PostStart() override;
	void Tick() override;
	void Spawn(float2 dir);
	
	void SetIndex(int index) { _index = index; }
	void SetFrame(int frame);

	Bullet(BulletPool* pool = nullptr);

	

private:

	void CheckCollision();
	void Move();
	void Despawn();
	void Timer();

	float2 _moveDir = { 1.0f, 0.0f };
	float _moveSpeed = 400.0f;

	int _dmg = 1;
	float _lifeTime = 4.0f;
	float _timer = 0.0f;

	int _index = 0; // Index in bullet pool

	Animator* _anim = nullptr;
	RectCollider* _col = nullptr;

	BulletPool* _pool = nullptr;
};

