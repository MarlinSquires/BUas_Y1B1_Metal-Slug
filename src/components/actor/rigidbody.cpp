#include "precomp.h"
#include "colliders/collider.h"
#include "collisionSystem.h"
#include "rigidbody.h"

#include "central.h"



void Rigidbody::Start()
{
	_col = GetGameObject()->GetComponent<Collider>();
}

void Rigidbody::Tick()
{
	GroundCheck();
	Gravity();
	Move();
}


CollisionResult Rigidbody::CheckCollision(float2 velocityVector)
{
	return (_col->CollideWith(CollisionLayerName::Solids, GetGameObject()->GetWorldPos() + velocityVector));
}

// Split check into x and y components, and also includes accel integration (adding half value)
void Rigidbody::Move()
{
	velocity += _accel / 2;

	
	// X check and pos update
	CollisionResult crX = CheckCollision(float2(velocity.x * Central::dts, 0.0f));
	if (crX.collided)
	{
		GetGameObject()->SetPos(float2(crX.resolvedPos.x, GetGameObject()->GetWorldPos().y));
		velocity.x = 0.0f;
	}

	GetGameObject()->UpdatePos(float2(velocity.x * Central::dts, 0.0f));
	

	
	// Y check and pos update
	CollisionResult crY = CheckCollision(float2(0.0f, velocity.y * Central::dts));
	if (crY.collided)
	{
		GetGameObject()->SetPos(float2(GetGameObject()->GetWorldPos().x, crY.resolvedPos.y));
		velocity.y = 0.0f;
	}

	GetGameObject()->UpdatePos(float2(0.0f, velocity.y * Central::dts));
	
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