#include "precomp.h"
#include "collisionSystem.h"
#include "collider.h"
#include "central.h"
#include "utils.h"


#pragma region Structors
Collider::Collider(int layer) : layer(layer)
{
	index = CollisionSystem::Register(layer, this);
}


Collider::Collider(int layer, Tmpl8::float2 offset) : layer(layer), offset(offset) 
{
	index = CollisionSystem::Register(layer, this);
};

Collider::~Collider()
{
	CollisionSystem::Deregister(layer, index); // Causes an issue on program shutdown - need to fix later
}
#pragma endregion


void Collider::Tick()
{
	DrawCollider();
}






