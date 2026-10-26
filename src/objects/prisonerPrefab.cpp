#include "precomp.h"
#include "prisonerPrefab.h"

#include "gameObject.h"
#include "prisoner.h"
#include "spriteRenderer.h"
#include "rectCollider.h"

#include "collisionSystem.h"
#include "renderSystem.h"

GameObject* PrisonerPrefab::Load(float2 spawnPos) 
{
	GameObject* go = new GameObject(spawnPos);
	go->AddComponent<Prisoner>();
	SpriteRenderer& spr = go->AddComponent<SpriteRenderer>(RenderLayerName::BGActors, new Sprite(new Surface("assets/prisoner.png"), 1));
	go->AddComponent<RectCollider>(CollisionLayerName::Enemies, spr.GetSprite());
	return go;
}