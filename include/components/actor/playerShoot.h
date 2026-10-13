#pragma once
#include "component.h"

#include "gun.h"

class Gun;
class LineRenderer;

// Handles player shooting logic


class PlayerShoot : public Component
{
public:

	void Start() override;
	void Tick() override;

	void SetGun(Gun gun) { _gun = gun; };

private:

	void Shoot();
	void HandleInputs();
	void LerpAim();
	void ShowAim();

	float2 _aimVector = { 1.0f, 0.0f }; // current aim vector, lerps towards targetVector
	float2 _targetVector = { 0.0f, 0.0f }; // target aim vector

	float _aimRate = 50.0f;
	bool _wantsToShoot = false;


	LineRenderer* _rend = nullptr; // Shows aim vector
	Gun _gun;
	TheApp* _game = nullptr; // Used for inputs

};

