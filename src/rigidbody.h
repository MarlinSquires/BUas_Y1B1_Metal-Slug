#pragma once
#include "component.h"


class Rigidbody : public Component
{
public:

	void Start() override;
	void Tick() override;


private:

	float grav = 0.05f;
	bool grounded;

	void CheckGrounded();

	Collider* col;



};
