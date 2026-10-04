#include "precomp.h"
#include "rigidbody.h"
#include "enemy.h"
#include "central.h"



void Enemy::Start()
{
	_rb = gameObject->GetComponent<Rigidbody>();

}

void Enemy::Tick()
{
	//if (abs(_rb->velocity.x > _maxSpeed)) return;
	_rb->AddForce(float2(_accel * Central::dts, 0.0f));

}