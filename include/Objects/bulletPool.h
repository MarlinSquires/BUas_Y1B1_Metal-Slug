#pragma once

class Bullet;


class BulletPool
{
public:

	void InstantiateToPool();

	Bullet* SpawnFromPool(); // Called by gun
	void ReturnToPool(Bullet* b, int index); // Called by bullet


	BulletPool();


private:


	static const int POOLSIZE = 100;

	Bullet* _objects[POOLSIZE];
	int _indices[POOLSIZE]; // Holds all the currently free indices

	
	int _freeCount = 0; // Number of objects currently in pool





};

