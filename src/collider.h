#pragma once
#include "component.h"

enum class CollisionLayerType;

enum class ColliderType
{
	Rect,
	Tile,
	Pixel
};

class Collider : public Component
{
public:

	virtual bool CollideWith(CollisionLayerType layer, float2 pos);

	// Getters
	ColliderType GetType() { return type; }
	bool overlapping = false;
	
	// Structors
	Collider(ColliderType colliderType, CollisionLayerType layer); // Set collision layer
	Collider(ColliderType colliderType, CollisionLayerType layer, Tmpl8::float2 offset); // Init with offset
	~Collider() = 0; // Used to deregister from CollisionSystem::colliders


protected:

	Tmpl8::float2 offset = float2(0.0f, 0.0f); //offset from GO origin
	

	ColliderType type;
	CollisionLayerType layer;
	int index;

};
