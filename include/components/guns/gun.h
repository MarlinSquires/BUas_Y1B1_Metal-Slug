#pragma once
#include "component.h"

class GameObject;

// Guns handle bullet shooting
// They are owned by both the player and enemies

// This class handles the basic gun, derived classes handle unique gun types

class Gun
{
public:

	virtual void Shoot(float2 dir);

	void SetGameObject(GameObject* go) { _go = go; }

	Gun(GameObject* go = nullptr) : _go(go) {};

protected: 

	float2 _firePoint = { 0.0f, 0.0f }; // Bullet spawn point - offset relative to owning gameObject

	GameObject* _go;

	float _fireDelay = 0.0f;
	int _damage = 1;

};

