#include "precomp.h"
#include "collisionSystem.h"
#include "gridCollider.h"




GridCollider::GridCollider(Grid* grid) : Collider(ColliderType::Tile, CollisionLayerType::Tiles), grid(grid) {};






