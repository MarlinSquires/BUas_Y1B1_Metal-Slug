#pragma once
#include "component.h"

enum class CollisionLayerType;

enum class ColliderType
{
	Rect,
	Tile,
	Pixel
};

struct CollisionResult;

class Collider : public Component
{
public:

	virtual  CollisionResult CollideWith(CollisionLayerType layer, float2 pos);

	// Getters
	const ColliderType GetType() const { return type; } 
	bool overlapping = false;
	
	// Structors
	Collider(ColliderType colliderType, CollisionLayerType layer); // Set collision layer
	Collider(ColliderType colliderType, CollisionLayerType layer, Tmpl8::float2 offset); // Init with offset
	~Collider() = 0; // Used to deregister from CollisionSystem::colliders


protected:

	float2 offset = { 0.0f, 0.0f }; //offset from GO origin
	
	int index;
	ColliderType type;
	CollisionLayerType layer;
	

};
