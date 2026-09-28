#include "precomp.h"
#include "collider.h"
#include "rigidbody.h"
#include "collisionSystem.h"
#include "central.h"



void Rigidbody::Start()
{
	_col = gameObject->GetComponent<Collider>();
}

void Rigidbody::Tick()
{
	GroundCheck();
	Gravity();
}


bool Rigidbody::CheckCollision(float2 moveVector)
{
	return (_col->CollideWith(CollisionLayerType::Tiles, gameObject->pos + moveVector));
}

void Rigidbody::Move(float2 moveVector)
{
	if (CheckCollision(moveVector)) return;
	gameObject->pos += moveVector;
}

void Rigidbody::AddForce(const float2 accelVector)
{
	velocity += accelVector / 2;
	Move(velocity * Central::dts);
	velocity += accelVector / 2;
}

void Rigidbody::Gravity()
{
	if (!_grounded && (velocity.y < _maxFallSpeed))
		AddForce(float2(0.0f, _grav * Central::dts));
}






void Rigidbody::GroundCheck()
{
	if (CheckCollision(float2(0.0f, _grav * Central::dts)))
	{
		//printf("Ground Collision!\n");
		velocity.y = clamp(velocity.y, -INFINITY, 0.0f);
		_grounded = true; // Ground check
	}

	else _grounded = false;
}