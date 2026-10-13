#include "precomp.h"
#include "central.h"

#include "guns/gun.h"
#include "guns/bullet.h"
#include "bulletPool.h"


#include "animator.h"
#include "colliders/rectCollider.h"
#include "renderers/rectRenderer.h"

#include "animationTypes.h"
#include "collisionSystem.h"
#include "renderSystem.h"

void Gun::Shoot(float2 dir)
{
	Bullet* b = Central::pool->SpawnFromPool();

	if (!b) return;
	
	b->Spawn(dir);
	b->GetGameObject()->SetPos(_go->GetWorldPos() + _firePoint);
}






