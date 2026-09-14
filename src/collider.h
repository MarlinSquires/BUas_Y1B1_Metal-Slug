//#pragma once
#include "component.h"

class RectCollider;
class TileCollider;
class PixelCollider;

class Collider : public Component
{
public:

	void Tick() override;

	virtual bool CollideWith(const Collider* other) = 0;

	// Double dispatch pattern
	virtual bool RectCollide(const RectCollider* other) = 0; // Does an AABB check
	virtual bool TileCollide(const TileCollider* other) = 0; // Checks against tilemap array
	virtual bool PixelCollide(const PixelCollider* other) = 0; // Checks against individual sprite pixels


	// Structors
	Collider(int layer); // Set collision layer

	Collider(int layer, Tmpl8::float2 offset); // Init with offset

	~Collider(); // Used to deregister from CollisionSystem::colliders


private:

	Tmpl8::float2 offset = float2(0.0f, 0.0f); //offset from GO origin

	int layer;
	int index;

	virtual void DrawCollider(); // Bool set by gameObject

};
