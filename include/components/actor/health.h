#pragma once
#include "component.h"

class Health : public Component
{
public:

	// Logic
	void TakeDamage(int dmg);
	

	// Getters
	int GetMaxHP() const{ return _maxHP; }
	int GetHP() const { return _hp; }
	bool ShouldDie() const { return _shouldDie; }


	// Structors
	Health(int hp) : _maxHP(hp), _hp(hp) {}


private:

	int _maxHP;
	int _hp;
	bool _shouldDie = false;

};


