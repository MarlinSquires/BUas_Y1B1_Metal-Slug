#pragma once
#include "component.h"

// Rigidbodies are used to move actors while checking for tile collisions

class Collider;
struct CollisionResult;

class Rigidbody : public Component
{
public:

	void Start() override;
	void Tick() override;

	void AddForce(float2 accelVector); // Alters the object's velocity vector

	bool Grounded() { return _grounded; }

	float2 velocity;

private:

	float2 accel;

	// Gravity
	const float _grav = 220.0f;
	const float _maxFallSpeed = 180.0f;
	
	void Move(float2 moveVector); // Linearly move object, checks against collisions
	void Gravity();
	CollisionResult CheckCollision(float2 moveVector);

	void GroundCheck();
	bool _grounded = false;;

	Collider* _col;
};
