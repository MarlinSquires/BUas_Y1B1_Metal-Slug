#pragma once
#include "collider.h"


// Collider using AABB


class RectCollider : public Collider
{
public:

	void Start() override;
	void Tick() override;


	bool CollideWith(const Collider* other) override;
	
	bool RectCollide(const RectCollider* other) override;
	bool TileCollide(const TileCollider* other) override;
	bool PixelCollide(const PixelCollider* other) override;


	void UpdateRect(Tmpl8::float2 pos);

	// Check if current object would collide with another object at X position
	bool CollideAt(Tmpl8::float2 pos, Collider* go); // Check against single object, faster
	bool CollideAt(Tmpl8::float2 pos, int layer); // Check against system's collider array

	// Same as CollideAt, but returns collision instance
	//Collider* CollideWith(Tmpl8::float2 pos, Collider* go);
	//Collider* CollideWith(Tmpl8::float2 pos, int layer);

	// Move gameObject by nDistance, if it would not collide
	void MoveAndCollide(int layer, Tmpl8::float2 distance);


	Tmpl8::float2 GetP1() { return p1; }
	Tmpl8::float2 GetP2() { return p2; }

	void DrawCollider() override;


	// Structors
	RectCollider(int layer, Tmpl8::Sprite* sprite); // Initialize thru sprite size

	RectCollider(int layer, Tmpl8::float2 size); // Initialize with manual size


private:


	Tmpl8::float2 p1; // xMin, yMin
	Tmpl8::float2 p2; // xMax, yMax

	Tmpl8::float2 size; // width, height

	// I really like snake_case here but PascalCase in other places...
	void DrawCollider(); // Bool set by gameObject


};

