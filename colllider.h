#pragma once
#include "component.h"


class Collider : public Component
{
public:

	void Start() override;
	void Tick() override;


	// Check if current object would collide with another object at X position
	bool CollideAt(Tmpl8::float2 pos, Collider* go); // Check against single object, faster
	bool CollideAt(Tmpl8::float2 pos, std::string layer); // Check against system's collider array

	// Same as CollideAt, but returns collision instance
	Collider* CollideWith(Tmpl8::float2 pos, Collider* go);
	Collider* CollideWith(Tmpl8::float2 pos, std::string layer);

	// Move gameObject by nDistance, if it would not collide
	void MoveAndCollide(std::string layer, Tmpl8::float2 distance);



	Tmpl8::float2 GetP1() { return p1; }
	Tmpl8::float2 GetP2() { return p2; }


	// Structors
	Collider(std::string layer, Tmpl8::Sprite* sprite); // Initialize thru sprite size

	Collider(std::string layer, Tmpl8::float2 size); // Initialize with manual size

	~Collider(); // Used to deregister from CollisionSystem::colliders


private:

	Tmpl8::float2 p1; // xMin, yMin
	Tmpl8::float2 p2; // xMax, yMax

	Tmpl8::float2 size; // width, height

	//CollisionSystem* collisionSystem;
	std::string layer;




	void UpdateRect(Tmpl8::float2 pos);

	// I really like snake_case here but PascalCase in other places...
	void DrawCollider(); // Bool set by gameObject

};
