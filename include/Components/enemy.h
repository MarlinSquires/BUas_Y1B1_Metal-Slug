#pragma once
#include "component.h"


class Enemy : public Component
{
public:
	void Start() override;
	void Tick() override;

private:
	Rigidbody* _rb;
	float _accel = 5.0f;
	float _maxSpeed = 50.0f;


};

