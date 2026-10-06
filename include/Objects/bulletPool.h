#pragma once

#include "bulletPool.h"

class Bullet;


class BulletPool
{
public:

	Bullet* SpawnFromPool(); // Called by gun
	void ReturnToPool(Bullet* b); // Called by bullet


	BulletPool(int poolSize);


private:

	void InstantiateToPool();

	Bullet** _objects;

	int _poolSize = 0;
	int _objectCount = 0; // Number of objects currently in pool





};

