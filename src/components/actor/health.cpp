#include "precomp.h"

#include "health.h"





void Health::TakeDamage(int dmg)
{
	assert(dmg > 0);

	
	_hp -= dmg;

	//printf("took damage, hp = %d\n", _hp);

	if (_hp <= 0) _shouldDie = true;
}