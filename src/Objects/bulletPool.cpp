#include "precomp.h"
#include "gameObject.h"
#include "bulletPool.h"
#include "central.h"

#include "guns/bullet.h"
#include "animator.h"
#include "colliders/rectCollider.h"
#include "renderers/rectRenderer.h"

#include "animationTypes.h"
#include "collisionSystem.h"
#include "renderSystem.h"


BulletPool::BulletPool() 
{
	Central::pool = this;
};


void BulletPool::InstantiateToPool()
{
	for (int i = 0; i < POOLSIZE; i++)
	{
		GameObject* go = new GameObject();
		go->SetActive(false);
		
		// Add bullet component
		_objects[i] = &go->AddComponent<Bullet>(this);
		_objects[i]->SetIndex(i);
		_indices[_freeCount++] = i;
	}
}

Bullet* BulletPool::SpawnFromPool()
{
	if (_freeCount <= 0) return nullptr;

	int index = _indices[--_freeCount];
	Bullet* b = _objects[index];
	b->GetGameObject()->SetActive(true);
	
	return b;
}


void BulletPool::ReturnToPool(Bullet* b, int index)
{
	_indices[_freeCount++] = index;

	b->GetGameObject()->SetActive(false);
}