#include "precomp.h"

#include "collisionSystem.h"
#include "collider.h"



#pragma region Structors
Collider::Collider(ColliderType colliderType, CollisionLayerType layer) : type(colliderType), layer(layer)
{
	index = CollisionSystem::Register(layer, this);
}

Collider::Collider(ColliderType colliderType, CollisionLayerType layer, Tmpl8::float2 offset) : type(colliderType), layer(layer), offset(offset)
{
	index = CollisionSystem::Register(layer, this);
};

Collider::~Collider()
{
	CollisionSystem::Deregister(layer, index); // Causes an issue on program shutdown - need to fix later
}
#pragma endregion



CollisionResult Collider::CollideWith(CollisionLayerType layer, float2 pos)
{
	 return CollisionSystem::Query(this, layer, pos);
}




