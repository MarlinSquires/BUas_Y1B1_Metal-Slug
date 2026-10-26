#include "precomp.h"
#include "collisionSystem.h"
#include "grid.h"
#include "gridCollider.h"
#include "gridFactory.h"


// Instantiates the GridSpawner
GridCollider::GridCollider(Grid& g) : Collider(ColliderType::Tile, CollisionLayerName::Solids) 
{
	_grid = &g;
};






