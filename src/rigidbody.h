#pragma once
#include "component.h"

// Rigidbodies are used to move actors while checking for tile collisions

class Collider;


class Rigidbody : public Component
{
public:

	void Start() override;
	void Tick() override;

	void AddForce(float2 accelVector); // Alters the object's velocity vector

	bool Grounded() { return _grounded; }

	float2 velocity;

private:

	// Gravity
	const float _grav = 220.0f;
	const float _maxFallSpeed = 180.0f;
	
	bool _grounded = false;;

	void Move(float2 moveVector); // Linearly move object, checks against collisions
	void Gravity();
	bool CheckCollision(float2 moveVector);
	void GroundCheck();


	Collider* _col;



};
