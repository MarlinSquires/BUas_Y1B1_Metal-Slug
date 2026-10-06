#pragma once
#include "component.h"

class Gun;

// Handles player shooting logic


class PlayerShoot : public Component
{
public:

	void Start() override;
	void Tick() override;



private:

	void HandleInputs();
	void LerpAim();

	float2 _aimVector = { 0.0f, 0.0f }; // current aim vector, lerps towards targetVector
	float2 _targetVector = { 0.0f, 0.0f }; // target aim vector

	float _aimRate = 1.0f;

	Gun* _gun = nullptr;
	Game* _game;

};

