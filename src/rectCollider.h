#pragma once
#include "collider.h"


// Collider using AABB


class RectCollider : public Collider
{
public:

	void Start() override;
	void Tick() override;

	// Move gameObject by nDistance, if it would not collide
	void MoveAndCollide(int layer, Tmpl8::float2 distance);

	void UpdateRect(Tmpl8::float2 pos);
	void SetScale(float xScale, float yScale);
	
	const float2 GetSize() { return _size; };
	const float2 GetP1() { return _p1; }
	const float2 GetP2() { return _p2; }

	// Structors
	RectCollider(CollisionLayerType layer, Sprite* sprite, float2 scale = float2(1.0f, 1.0f)); // Initialize thru sprite size
	RectCollider(CollisionLayerType layer, float2 size, float2 scale = float2(1.0f, 1.0f)); // Initialize with manual size

private:

	float2 _p1 = float2(0.0f, 0.0f); // xMin, yMin
	Tmpl8::float2 _p2 = float2(0.0f, 0.0f); // xMax, yMax

	float2 _size = float2(0.0f, 0.0f); // width, height
	float2 _scale = float2(1.0f, 1.0f);


};

