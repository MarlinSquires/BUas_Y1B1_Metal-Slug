#pragma once
#include "component.h"

// Rigidbodies are used to move actors while checking for tile collisions

class Collider;
struct CollisionResult;

class Rigidbody : public Component
{
public:

	// Lifecycle
	void Start() override;
	void Tick() override;

	// Logic
	void AddForce(float2 accelVector); // Alters the object's velocity vector
	void Friction(float friction);

	// Getters
	bool Grounded() const { return _grounded; }

	float2 velocity{ 0.0f, 0.0f };

private:

	void Move(); // Linearly move object, checks against collisions

	float2 _accel;

	// Gravity
	const float _grav = 1020.0f;
	const float _maxFallSpeed = 380.0f;
	bool _grounded = false;;


	Collider* _col = nullptr;
	
	void Gravity();
	void GroundCheck();

	CollisionResult CheckCollision(float2 moveVector);

};
