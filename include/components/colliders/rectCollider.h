#pragma once
#include "collider.h"


// Collider using AABB


class RectCollider : public Collider
{
public:

	void Start() override;
	void Tick() override;

	void UpdateRect();

	// Setters
	void SetSize(float xSize, float ySize);
	void SetSize(Sprite* spr);
	void SetScale(float xScale, float yScale);
	void SetOffset(float xOffset, float yOffset);
	
	// Getters
	float2 GetSize() const { return _size; };
	float2 GetP1() const { return _p1; } // Returns actual P1 / P2
	float2 GetP2() const { return _p2; }

	float2 GetP1(float2 pos) const; // Returns where P1 and P2 would be were the collider in an arbitrary position
	float2 GetP2(float2 pos) const;


	// Structors
	//RectCollider(CollisionLayerName layer, float2 scale = float2(1.0f, 1.0f));
	RectCollider(CollisionLayerName layer, Sprite* sprite, float2 scale = float2(1.0f, 1.0f)); // Initialize thru sprite size
	RectCollider(CollisionLayerName layer, float2 size = {0.0f, 0.0f}, float2 scale = float2(1.0f, 1.0f)); // Initialize with manual size

private:

	float2 _p1 = float2(0.0f, 0.0f);; // xMin, yMin
	float2 _p2 = float2(0.0f, 0.0f);;// xMax, yMax

	float2 _size = {}; // width, height
	float2 _scale = float2(1.0f, 1.0f);
	float2 _offset = float2(0.0f, 0.0f);


};

