#include "precomp.h"

#include "collider.h"
#include "rectCollider.h"
#include "gridCollider.h"
#include "pixelCollider.h"

#include "collisionSystem.h"
#include "grid.h"

#include "central.h"
#include "utils.h"


int CollisionSystem::Register(const CollisionLayerName collisionLayer, Collider* col)
{
	CollisionLayer& layer = collisionLayers[static_cast<int>(collisionLayer)];
	assert(layer.count < layer.SIZE);
	layer.colliders[layer.count++] = col;
	return layer.count - 1; // Return val is used to set collider index
}

void CollisionSystem::Deregister(const CollisionLayerName collisionLayer, int index)
{
	CollisionLayer& layer = collisionLayers[static_cast<int>(collisionLayer)];
	assert(index >= 0 && index < layer.count);

	layer.colliders[index] = layer.colliders[--layer.count];
	layer.colliders[index]->index = index;
	layer.colliders[layer.count] = nullptr;
}


CollisionResult CollisionSystem::Query(const Collider& col, const CollisionLayerName collisionLayer, const float2 pos)
{
	// Only rectColliders and pixelColliders will be passed into here, no need for a tileCollider to ever be passed
	
	CollisionLayer& layer = collisionLayers[static_cast<int>(collisionLayer)];

	for (int i = 0; i < layer.count; i++)
	{
		Collider& col2 = *layer.colliders[i];
		if (&col2 == &col) continue; // Stop self-collision

		if (col.GetType() == ColliderType::Rect)
		{
			if (col2.GetType() == ColliderType::Rect)
			{
				// Pass layer to prevent expensive position resolution against non-solid rects
				CollisionResult cr = (RectVsRect(collisionLayer, static_cast<const RectCollider&>(col), static_cast<const RectCollider&>(col2), pos));
				if (cr.collided == true) return cr;
				else continue;
			}
			else if (col2.GetType() == ColliderType::Tile)
			{
				CollisionResult cr = (RectVsTile(static_cast<const RectCollider&>(col), static_cast<GridCollider&>(col2), pos));
				if (cr.collided == true) return cr;
				else continue;
			}
			/*else
			{
				if (RectVsPixel(static_cast<RectCollider&>(col), static_cast<PixelCollider&>(col2), pos)) return true;
			}*/
		}

		//else // Don't need to check if type == pixel, because we only check two col1 types
		//{
		//	if (col2.GetType() == ColliderType::Tile)
		//	{
		//		if (PixelVsTile(static_cast<PixelCollider&>(col), static_cast<GridCollider&>(col2), pos)) return true;
		//	}
		//	else if (col2.GetType() == ColliderType::Pixel)
		//	{
		//		if (PixelVsPixel(static_cast<PixelCollider&>(col), static_cast<PixelCollider&>(col2), pos)) return true;
		//	}
		//}
	}
	return CollisionResult(false);
}

	


CollisionResult CollisionSystem::RectVsRect(CollisionLayerName collisionLayer, const RectCollider& rectCol1, const RectCollider& rectCol2, const float2 pos)
{
	if (!rectCol2.active) return CollisionResult(false);

	float2 originalPos = rectCol1.GetGameObject()->GetWorldPos();

	const float2 col1P1 = rectCol1.GetP1(pos);
	const float2 col1P2 = rectCol1.GetP2(pos);

	const float2 col2P1 = rectCol2.GetP1();
	const float2 col2P2 = rectCol2.GetP2(); 

	// AABB logic
	bool xCollision = CheckCollisionAxis(col1P1.x, col1P2.x, col2P1.x, col2P2.x);
	bool yCollision = CheckCollisionAxis(col1P1.y, col1P2.y, col2P1.y, col2P2.y);


	if (xCollision && yCollision)
	{
		//printf("I'm colliding!!!\n");
		CollisionResult cr = { true };

		// Handle resolution
		if (collisionLayer == CollisionLayerName::Solids)
		{
			char xDir = (char)utils::sign(pos.x - originalPos.x);
			char yDir = (char)utils::sign(pos.y - originalPos.y);

			float xPos = rectCol2.GetGameObject()->GetWorldPos().x + (((rectCol1.GetSize().x / 2) + (rectCol2.GetSize().x / 2)) * -xDir);
			float yPos = rectCol2.GetGameObject()->GetWorldPos().y + (((rectCol1.GetSize().y / 2) + (rectCol2.GetSize().y / 2)) * -yDir);

			cr.resolvedPos = { xPos, yPos };
		}
		
		cr.col = &rectCol2;
		return cr;
	}
	
	// No collision found	
	return CollisionResult(false);
}





CollisionResult CollisionSystem::RectVsTile(const RectCollider& rectCol, GridCollider& tileCol, const float2 pos)
{
	// Init grid values
	Grid& grid = tileCol.GetGrid();
	int tileSize = grid.tileSize;
	int arrayMax = grid.width * grid.height - 1;


	float2 originalPos = rectCol.GetGameObject()->GetWorldPos();
	float2 prevP1 = rectCol.GetP1();
	float2 prevP2 = rectCol.GetP2();

	float2 p1 = rectCol.GetP1(pos);
	float2 p2 = rectCol.GetP2(pos);

	int xmin = (int)floorf(p1.x / tileSize); // Leftmost tile being overlapped
	int ymin = (int)floorf(p1.y / tileSize); // Topmost tile being overlapped

	int xmax = (int)ceilf(p2.x / tileSize) - 1; // Rightmost
	int ymax = (int)ceilf(p2.y / tileSize) - 1; // Bottommost

	// Loop over all overlapping tiles positions and check for solidity
	for (int y = ymin; y <= ymax; y++)
	{
		if (y < 0 || y >= grid.height) continue; // Ensure you cant check outside array

		for (int x = xmin; x <= xmax; x++)
		{
			if (x < 0 || x >= grid.width) continue; 

			int i = x + y * grid.width;

			TileType tileType = grid.tiles[i];

			switch (tileType)
			{
			default: // Cant return false here because it would exit func before checking all tile positions
				break;
				
			case TileType::Solid:
			{
				// Determine direction between GO and colliding tile1
				char xDir = (char)utils::sign(pos.x - originalPos.x);
				char yDir = (char)utils::sign(pos.y - originalPos.y);

				char offsetX = (xDir == 1) ? 0 : (char)tileSize;
				char offsetY = (yDir == 1) ? 0 : (char)tileSize;

				float xPos = (x * tileSize + offsetX + ((rectCol.GetSize().x / 2) * - xDir));
				float yPos = (y * tileSize + offsetY + ((rectCol.GetSize().y / 2) * - yDir));

				return CollisionResult(true, float2(xPos, yPos));
			}
				
			case TileType::Passthrough:
				if ((y * tileSize > static_cast<int>(prevP2.y)))
				{
					float yPos = (y * tileSize - ((rectCol.GetSize().y / 2)));
					return CollisionResult(true, float2(0.0f, yPos));
				}
					
				else break;
			}
		}
	}

	// Sloped tile checks

	float relRightX = 0;
	float relRightY = 0;
	float relLeftX = 0;
	float relLeftY = 0;

	// Slopeleft check, don't want to iterate over every overlapped tile, only the bottomright-most tile
	int bottomRightTile = xmax + ymax * grid.width;
	if (bottomRightTile < 0 || bottomRightTile > arrayMax ) return CollisionResult(false);

	if (grid.tiles[bottomRightTile] == TileType::SlopeLeft)
	{
		// only need to check the rightmost corner of the rect
		relRightX = p2.x - xmax * tileSize;
		relRightY = p2.y - ymax * tileSize;
		if (relRightX + relRightY + 2 >= tileSize) // Why do we need +2 here for it to align correctly?
		{
			CollisionResult cr = { true };
			cr.resolvedPos = float2(pos.x, ymax * tileSize + tileSize - relRightX - (rectCol.GetSize().y / 2) - 3);  // -3 here
			return cr; 
		}
	}

	int bottomLeftTile = xmin + ymax * grid.width;
	if (bottomLeftTile < 0 || bottomLeftTile > arrayMax) return CollisionResult(false);
	if (grid.tiles[bottomLeftTile] == TileType::SlopeRight)
	{
		// only need to check the lefttmost corner of the rect
		relLeftX = p1.x - xmin * tileSize;
		relLeftY = p2.y - ymax * tileSize;
		if (relLeftY >= relLeftX)
		{
			CollisionResult cr = { true };
			cr.resolvedPos = float2(pos.x, ymax * tileSize + relLeftX - tileSize - (rectCol.GetSize().y / 2));
			return cr;
		}
	}

	return CollisionResult(false);
}




//bool CollisionSystem::CollisionSystem::RectVsPixel(RectCollider& rectCol, PixelCollider& pixelCol, float2 pos)
//{
//
//	return false;
//
//}
//
//bool CollisionSystem::PixelVsTile(PixelCollider& pixelCol, GridCollider& tileCol, float2 pos)
//{
//
//	return false;
//
//}
//bool CollisionSystem::PixelVsPixel(PixelCollider& pixelCol1, PixelCollider& pixelCol2, float2 pos)
//{
//
//	return false;
//
//
//}





// For AABB collision checking
bool CollisionSystem::CheckCollisionAxis(float aMin, float aMax, float bMin, float bMax)
{
	return aMin < bMax && aMax > bMin;
}






