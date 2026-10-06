#include "precomp.h"
#include "gun.h"
#include "bulletPool.h"
#include "central.h"


void Gun::Shoot()
{
	Bullet* b = Central::pool->SpawnFromPool();



}






