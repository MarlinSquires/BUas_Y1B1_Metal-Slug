//#pragma once
//#include "component.h"
//
//
//class Collider : public Component
//{
//public:
//
//	void Start() override;
//	void Tick() override;
//
//	void UpdateRect(Tmpl8::float2 pos);
//
//	// Check if current object would collide with another object at X position
//	bool CollideAt(Tmpl8::float2 pos, Collider* go); // Check against single object, faster
//	bool CollideAt(Tmpl8::float2 pos, int layer); // Check against system's collider array
//
//	// Same as CollideAt, but returns collision instance
//	Collider* CollideWith(Tmpl8::float2 pos, Collider* go);
//	Collider* CollideWith(Tmpl8::float2 pos, int layer);
//
//	// Move gameObject by nDistance, if it would not collide
//	void MoveAndCollide(int layer, Tmpl8::float2 distance);
//
//
//
//	Tmpl8::float2 GetP1() { return p1; }
//	Tmpl8::float2 GetP2() { return p2; }
//
//
//	// Structors
//	Collider(int layer, Tmpl8::Sprite* sprite); // Initialize thru sprite size
//
//	Collider(int layer, Tmpl8::float2 size); // Initialize with manual size
//
//	Collider(int layer, Tmpl8::float2 size, Tmpl8::float2 offset); // Init with offset
//
//	~Collider(); // Used to deregister from CollisionSystem::colliders
//
//
//private:
//
//	Tmpl8::float2 p1; // xMin, yMin
//	Tmpl8::float2 p2; // xMax, yMax
//
//	Tmpl8::float2 size; // width, height
//	Tmpl8::float2 offset = float2(0.0f, 0.0f); //offset from GO origin
//
//	int layer;
//	int index;
//
//
//	
//
//	// I really like snake_case here but PascalCase in other places...
//	void DrawCollider(); // Bool set by gameObject
//
//};
