#pragma once
#include "component.h"

class BulletPool;

class Bullet : public Component
{
	friend class BulletPool;

public:


	Bullet(BulletPool* pool);

private:

	void Despawn();

	float2 _moveDir = { 1.0f, 0.0f };
	float _moveSpeed = 0.0f;
	int _damage = 0;

	

	BulletPool* _pool;
	int _index = 0; // index in bullet pool

};

