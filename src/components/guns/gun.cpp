#include "precomp.h"
#include "central.h"
#include "utils.h"

#include "guns/gun.h"
#include "guns/bullet.h"
#include "bulletPool.h"


#include "animator.h"
#include "rectCollider.h"
#include "rectRenderer.h"
#include "spriteRenderer.h"

#include "animationTypes.h"
#include "collisionSystem.h"
#include "renderSystem.h"

void Gun::Shoot(float2 dir)
{
	Bullet* b = Central::pool->SpawnFromPool();

	if (!b) return;
	
	b->Spawn(dir);
	b->GetGameObject()->SetWorldPos(_go->GetWorldPos() + _firePoint);

	b->SetFrame(utils::dir_to_frame(dir));

}






