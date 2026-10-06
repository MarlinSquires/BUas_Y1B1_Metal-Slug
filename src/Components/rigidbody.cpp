#include "precomp.h"
#include "collider.h"
#include "collisionSystem.h"
#include "rigidbody.h"

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


CollisionResult Rigidbody::CheckCollision(float2 velocity)
{
	return (_col->CollideWith(CollisionLayerType::Tiles, gameObject->GetWorldPos() + velocity));
}

void Rigidbody::Move(float2 velocity)
{
	// Split check into x and y components
	CollisionResult crX = CheckCollision(float2(velocity.x, 0.0f));
	CollisionResult crY = CheckCollision(float2(0.0f, velocity.y));

	if (crX.collided)
	{
		velocity.x = 0;

		if (crX.resolved)
		{
			float2 newPos = { gameObject->GetWorldPos().x, crX.resolvedPos.y };
			gameObject->SetPos(newPos);
		}
	}

	if (crY.collided)
	{
		velocity.y = 0;
	}

	gameObject->SetPos(gameObject->GetWorldPos() + velocity);
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
	{
		CollisionResult cr = CheckCollision(float2(0.0f, 0.1f));
		velocity.y += _grav * Central::dts / 2;
		if (!cr.collided)
		{
			gameObject->SetPos({ gameObject->GetWorldPos().x, gameObject->GetWorldPos().y + velocity.y * Central::dts });
		}
			
		velocity.y += _grav * Central::dts / 2;
	}
}




void Rigidbody::GroundCheck()
{
	CollisionResult cr = CheckCollision(float2(0.0f, _grav * Central::dts));
	if (cr.collided)
	{
		//printf("Ground Collision!\n");
		velocity.y = clamp(velocity.y, -INFINITY, 0.0f);
		_grounded = true; // Ground check
	}

	else _grounded = false;
}