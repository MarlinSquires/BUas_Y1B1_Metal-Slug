#include "precomp.h"
#include "central.h"

#include "bulletPool.h"
#include "colliders/rectCollider.h"
#include "renderers/rectRenderer.h"
#include "animator.h"

#include "collisionSystem.h"
#include "renderSystem.h"
#include "animation/animationTypes.h"

#include "guns/bullet.h"
#include "health.h"


Bullet::Bullet(BulletPool* pool) : _pool(pool) {}


// Lifecycle
void Bullet::Start()
{
	_anim = &_gameObject->AddComponent<Animator>(RenderLayerName::BGActors, AnimationSetName::Projectiles);
	_col = &_gameObject->AddComponent<RectCollider>(CollisionLayerName::Bullets);
	
	_gameObject->AddComponent<RectRenderer>(_col);
	
}

void Bullet::PostStart()
{

	_col->SetSize(_anim->GetSprite());

}

void Bullet::Tick()
{
	Move();
	CheckCollision();
	Timer();
}

void Bullet::Spawn(float2 dir)
{
	_timer = _lifeTime;
	_moveDir = dir;
}


// Logic
void Bullet::Move()
{
	_gameObject->UpdateWorldPos(_moveDir * _moveSpeed * Central::dts);
}

void Bullet::CheckCollision()
{
	float2 pos = _gameObject->GetWorldPos();

	CollisionResult crt = _col->CollideWith(CollisionLayerName::Solids, pos);
	CollisionResult cre = _col->CollideWith(CollisionLayerName::Enemies, pos);

	if (crt.collided) Despawn();
	else if (cre.collided)
	{
		//printf("bullet hit enemy\n");
		Health* h = cre.col->GetGameObject()->GetComponent<Health>();
		if (h) h->TakeDamage(_dmg);
		Despawn();
	}

}

void Bullet::Timer()
{
	_timer -= Central::dts;

	if (_timer <= 0.0f) Despawn();
}


void Bullet::Despawn()
{
	_pool->ReturnToPool(this, _index);
}



void Bullet::SetFrame(int frame)
{
	_anim->SetFrame(frame);
}