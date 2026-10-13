#include "precomp.h"

#include "collisionSystem.h"
#include "colliders/collider.h"



#pragma region Structors
Collider::Collider(ColliderType colliderType, CollisionLayerName layer) : _type(colliderType), _layer(layer)
{
	index = CollisionSystem::Register(layer, this);
	//printf("registered, index: %d\n", index);
}

Collider::Collider(ColliderType colliderType, CollisionLayerName layer, Tmpl8::float2 offset) : _type(colliderType), _layer(layer), _offset(offset)
{
	index = CollisionSystem::Register(layer, this);
	//printf("registered, index: %d\n", index);
};

Collider::~Collider()
{
	CollisionSystem::Deregister(_layer, index); // Causes an issue on program shutdown - need to fix later
}
#pragma endregion



CollisionResult Collider::CollideWith(CollisionLayerName layer, float2 pos)
{
	 return CollisionSystem::Query(*this, layer, pos);
}




