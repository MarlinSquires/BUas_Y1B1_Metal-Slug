#pragma once
#include "component.h"

enum class CollisionLayerName : uint8_t;

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

	virtual  CollisionResult CollideWith(CollisionLayerName layer, float2 pos);

	// Getters
	ColliderType GetType() const { return _type; } 
	bool Overlapping() const { return _overlapping; }
	
	// Structors
	Collider(ColliderType colliderType, CollisionLayerName layer); // Set collision layer
	Collider(ColliderType colliderType, CollisionLayerName layer, Tmpl8::float2 offset); // Init with offset
	~Collider() = 0; // Used to deregister from CollisionSystem::colliders

	int index;

protected:

	float2 _offset = { 0.0f, 0.0f }; //offset from GO origin
	bool _overlapping = false;
	
	ColliderType _type;
	CollisionLayerName _layer;
	

};
