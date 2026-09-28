#include "precomp.h"
#include "collisionSystem.h"
#include "grid.h"
#include "gridCollider.h"
#include "gridFactory.h"


// Instantiates the GridSpawner
GridCollider::GridCollider(const char* address) : Collider(ColliderType::Tile, CollisionLayerType::Tiles) 
{
	GridFactory spawner = GridFactory();
	grid = spawner.BuildGrid(address);

};






