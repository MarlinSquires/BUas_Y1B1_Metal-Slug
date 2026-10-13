#include "precomp.h"
#include "collisionSystem.h"
#include "grid.h"
#include "colliders/gridCollider.h"
#include "gridFactory.h"


// Instantiates the GridSpawner
GridCollider::GridCollider(const char* address) : Collider(ColliderType::Tile, CollisionLayerName::Solids) 
{
	GridFactory spawner = GridFactory();
	_grid = spawner.BuildGrid(address);

};






