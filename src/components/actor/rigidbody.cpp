#include "precomp.h"
#include "colliders/collider.h"
#include "collisionSystem.h"
#include "rigidbody.h"

#include "central.h"



void Rigidbody::Start()
{
	_col = _gameObject->GetComponent<Collider>();
}

void Rigidbody::Tick()
{
	GroundCheck();
	Gravity();
	Move();
}


CollisionResult Rigidbody::CheckCollision(float2 velocityVector)
{
	return (_col->CollideWith(CollisionLayerName::Solids, _gameObject->GetWorldPos() + velocityVector));
}

// Split check into x and y components, and also includes accel integration (adding half value)
void Rigidbody::Move()
{
	velocity += _accel / 2;

	
	// X check and pos update
	CollisionResult crX = CheckCollision(float2(velocity.x * Central::dts, 0.0f));
	if (crX.collided)
	{
		_gameObject->SetWorldPos(float2(crX.resolvedPos.x, _gameObject->GetWorldPos().y));
		velocity.x = 0.0f;
	}

	_gameObject->UpdateWorldPos(float2(velocity.x * Central::dts, 0.0f));
	

	
	// Y check and pos update
	CollisionResult crY = CheckCollision(float2(0.0f, velocity.y * Central::dts));
	if (crY.collided)
	{
		_gameObject->SetWorldPos(float2(_gameObject->GetWorldPos().x, crY.resolvedPos.y));
		velocity.y = 0.0f;
	}

	_gameObject->UpdateWorldPos(float2(0.0f, velocity.y * Central::dts));
	
	velocity += _accel / 2;
	_accel = float2(0.0f, 0.0f);
}


void Rigidbody::AddForce(const float2 accelVector)
{
	_accel += accelVector * Central::dts;
}

void Rigidbody::Gravity()
{
	if (!_grounded && (velocity.y < _maxFallSpeed))
	{
		AddForce(float2(0.0f, _grav));
	}
}


void Rigidbody::Friction(float friction)
{
	if (velocity.x > 0.0f)
	{
		if (velocity.x > -friction)
		{
			AddForce(float2(-friction, 0.0f));
		}
		else AddForce(float2(-velocity.x, 0.0f));


		//if (velocity.x < 0.0f)
		//{
		//	velocity.x = 0.0f; // Stops overshoot
		//}
	}
	else if (velocity.x < 0.0f)
	{
		if (velocity.x < friction)
		{
			AddForce(float2(friction, 0.0f));
		}
		else AddForce(float2(velocity.x, 0.0f));

		
		//if (velocity.x > 0.0f)
		//{
		//	velocity.x = 0.0f; // Stops overshoot
		//}
	}
}




void Rigidbody::GroundCheck()
{
	CollisionResult cr = CheckCollision(float2(0.0f, 0.1f));
	if (cr.collided)
	{
		//printf("Ground Collision!\n");

		if (velocity.y > 0.0f) velocity.y = 0.0f;
		_grounded = true; // Ground check
	}

	else _grounded = false;
}