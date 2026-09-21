#include "precomp.h"
#include "collider.h"
#include "rigidbody.h"
#include "collisionSystem.h"



void Rigidbody::Start()
{
	col = gameObject->GetComponent<Collider>();
	//assert(col == nullptr);
}

void Rigidbody::Tick()
{
	CheckGrounded();

	if (!grounded)
	{
		gameObject->pos.y += grav;
	}
}

void Rigidbody::CheckGrounded()
{
	if (col->CollideWith(CollisionLayerType::Tiles, gameObject->pos + float2(0, grav)))
		grounded = true;
	else grounded = false;
}