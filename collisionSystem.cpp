#include "precomp.h"
#include "collider.h"
#include "collisionSystem.h"


void CollisionSystem::Register(int layer, Collider* col)
{
	CollisionLayer* l = layers[layer];
	l->colliders[l->colCount++] = col;
}

void CollisionSystem::Deregister(int layer, int index)
{
	CollisionLayer* l = layers[layer];
	l->colliders[index] = l->colliders[l->colCount--]

}






