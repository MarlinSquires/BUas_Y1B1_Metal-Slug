#pragma once
#include "component.h"

class Health : public Component
{
public:

	// Logic
	void TakeDamage(int dmg);
	bool ShouldDie() { return _shouldDie; }

	int GetMaxHP() { return _maxHP; }
	int GetHP() { return _hp; }


	// Structors
	Health(int hp) : _maxHP(hp), _hp(hp) {}


private:

	int _maxHP;
	int _hp;
	bool _shouldDie = false;

};


