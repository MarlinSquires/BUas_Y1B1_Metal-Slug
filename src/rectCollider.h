#pragma once
#include "collider.h"


// Collider using AABB


class RectCollider : public Collider
{
public:

	void Start() override;
	void Tick() override;



	void UpdateRect(Tmpl8::float2 pos);


	// Move gameObject by nDistance, if it would not collide
	void MoveAndCollide(int layer, Tmpl8::float2 distance);


	Tmpl8::float2 GetP1() { return p1; }
	Tmpl8::float2 GetP2() { return p2; }

	// Structors
	RectCollider(CollisionLayerType layer, Tmpl8::Sprite* sprite); // Initialize thru sprite size
	RectCollider(CollisionLayerType layer, Tmpl8::float2 size); // Initialize with manual size

private:

	Tmpl8::float2 p1 = float2(0.0f, 0.0f); // xMin, yMin
	Tmpl8::float2 p2 = float2(0.0f, 0.0f); // xMax, yMax

	Tmpl8::float2 size = float2(0.0f, 0.0f); // width, height


};

