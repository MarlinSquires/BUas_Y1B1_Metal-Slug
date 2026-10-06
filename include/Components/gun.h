#pragma once
#include "component.h"

// Guns handle bullet shooting
// They are owned by both the player and enemies

// This class handles the basic gun, derived classes handle unique gun types

class Gun : public Component
{

public:

	virtual void Shoot();


protected: 
	float2 _firePoint = { 0.0f, 0.0f }; // Bullet spawn point - offset relative to owning gameObject

	float _fireDelay = 0.0f;
	int _damage = 1;

	


};

