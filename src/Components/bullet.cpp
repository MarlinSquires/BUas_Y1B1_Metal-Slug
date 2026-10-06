#include "precomp.h"
#include "bullet.h"
#include "bulletPool.h"


Bullet::Bullet(BulletPool* pool) : _pool(pool)
{
}

void Bullet::Despawn()
{

	_pool->ReturnToPool(this);



}