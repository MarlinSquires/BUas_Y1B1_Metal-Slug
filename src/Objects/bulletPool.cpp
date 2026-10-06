#include "precomp.h"
#include "gameObject.h"
#include "bullet.h"
#include "bulletPool.h"
#include "central.h"


BulletPool::BulletPool(int poolSize) : _poolSize(poolSize) 
{
	_objects = new Bullet * [_poolSize]();
	Central::pool = this;
};


void BulletPool::InstantiateToPool()
{
	
	
	for (int i = 0; i < _poolSize; i++)
	{
		GameObject* go = new GameObject();
		go->SetActive(false);
		_objects[i] = &go->AddComponent<Bullet>(this);
		_objects[i]->_index = i;
		_objectCount++;
	}
}

Bullet* BulletPool::SpawnFromPool()
{
	Bullet* b = _objects[_objectCount--];
	b->gameObject->SetActive(true);
	return b;
}

void BulletPool::ReturnToPool(Bullet* b)
{
	if (b->_index > _objectCount)
	{
		Bullet* b2 = _objects[_objectCount]; // Cache bullet at top of 'stack'
		int i = b->_index; // cache b1 index

		b->_index = _objectCount; // Swap pos of b1 and b2
		_objects[_objectCount++] = b;
		_objects[i] = b2;
	}

	b->gameObject->SetActive(false);


}