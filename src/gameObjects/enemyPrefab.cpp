#include "precomp.h"
#include "enemyPrefab.h"

#include "gameObject.h"
#include "enemy.h"
#include "animator.h"
#include "colliders/rectCollider.h"
#include "renderers/spriteRenderer.h"
#include "renderers/rectRenderer.h"
#include "rigidbody.h"
#include "health.h"

#include "renderSystem.h"
#include "collisionSystem.h"
#include "animationTypes.h"




GameObject* EnemyPrefab::Load(float2 spawnPos, GameObject* player, EnemyType type)
{
	GameObject* go = new GameObject(spawnPos);

	go->AddComponent<Enemy>(type, player);

	go->AddComponent<Animator>(RenderLayerName::BGActors, AnimationSetName::Enemy);
	RectCollider& col = go->AddComponent<RectCollider>(CollisionLayerName::Enemies, float2(24.0f, 36.0f));
	go->AddComponent<RectRenderer>(&col);
	go->AddComponent<Rigidbody>();

	return go;

}


