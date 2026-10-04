#include "precomp.h"
#include "collider.h"
#include "rectCollider.h"
#include "gridCollider.h"
#include "pixelCollider.h"
#include "collisionSystem.h"
#include "grid.h"
#include "central.h"

#include <iostream>


CollisionSystem::~CollisionSystem()
{
	delete[] collisionLayers;
}


CollisionLayer CollisionSystem::collisionLayers[] = {
	CollisionLayer(),
	CollisionLayer(),
	CollisionLayer(),
	CollisionLayer(),
};


int CollisionSystem::Register(const CollisionLayerType collisionLayer, Collider* col)
{
	CollisionLayer& layer = collisionLayers[static_cast<int>(collisionLayer)];
	layer.colliders[layer.colCount++] = col;
	return layer.colCount - 1;
}

void CollisionSystem::Deregister(const CollisionLayerType collisionLayer, int index)
{
	CollisionLayer& layer = collisionLayers[static_cast<int>(collisionLayer)];
	layer.colliders[index] = layer.colliders[layer.colCount--];
}


CollisionResult CollisionSystem::Query(Collider* collider, const CollisionLayerType collisionLayer, const float2 pos)
{
	// Only rectColliders and pixelColliders will be passed into here, no need for a tileCollider to ever be passed
	
	CollisionLayer& layer = collisionLayers[static_cast<int>(collisionLayer)];
	Collider& col = *collider;

	for (int i = 0; i < layer.colCount; i++)
	{
		Collider& col2 = *layer.colliders[i];
		if (&col2 == collider) return false;

		if (col.GetType() == ColliderType::Rect)
		{
			if (col2.GetType() == ColliderType::Rect)
			{
				return (RectVsRect(static_cast<RectCollider&>(col), static_cast<RectCollider&>(col2), pos));
			}
			else if (col2.GetType() == ColliderType::Tile)
			{
				return (RectVsTile(static_cast<RectCollider&>(col), static_cast<GridCollider&>(col2), pos));
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
	return false;
}

	


CollisionResult CollisionSystem::RectVsRect(RectCollider& rectCol1, RectCollider& rectCol2, const float2 pos)
{
	if (!rectCol2.active) return CollisionResult(false);

	float2 originalPos = rectCol1.gameObject->GetWorldPos();

	// Move rect to check position
	rectCol1.UpdateRect(pos);

	const float2 colP1 = rectCol2.GetP1(); // float2 and pointer are both 8 bytes, so does it matter whther I pass by value or ptr / ref?
	const float2 colP2 = rectCol2.GetP2(); // Pass by pointer would cause more cache misses ??

	// AABB logic
	bool xCollision = CheckCollisionAxis(rectCol1.GetP1().x, rectCol1.GetP2().x, colP1.x, colP2.x);
	bool yCollision = CheckCollisionAxis(rectCol1.GetP1().y, rectCol1.GetP2().y, colP1.y, colP2.y);

	// Move rect back
	rectCol1.UpdateRect(originalPos);

	if (xCollision && yCollision)
	{
		//cout << "I'm colliding!!!" << endl;
		rectCol1.overlapping = true;
		rectCol2.overlapping = true;
		return CollisionResult(true);
	}
	
	// No collision found
	rectCol1.overlapping = false;
	rectCol2.overlapping = false;
	
	return CollisionResult(false);
}





CollisionResult CollisionSystem::RectVsTile(RectCollider& rectCol, GridCollider& tileCol, const float2 pos)
{
	float2 originalPos = rectCol.gameObject->GetWorldPos();
	float2 prevP1 = rectCol.GetP1();
	float2 prevP2 = rectCol.GetP2();

	// Convert worldspace positions to gridspace
	rectCol.UpdateRect(pos);

	Grid& grid = tileCol.GetGrid();
	int tileSize = grid.tileSize;
	int arrayMax = grid.width * grid.height;

	float2 p1 = rectCol.GetP1();
	float2 p2 = rectCol.GetP2();

	int xmin = (int)(p1.x / tileSize);
	int ymin = (int)(p1.y / tileSize);
	
	int xmax = (int)(p2.x / tileSize);
	int ymax = (int)(p2.y / tileSize);

	rectCol.UpdateRect(originalPos);

	float relRightX = 0;
	float relRightY = 0;
	float relLeftX = 0;
	float relLeftY = 0;

	// Loop over all overlapping tiles positions and check for solidity
	for (int y = ymin; y <= ymax; y++)
	{
		for (int x = xmin; x <= xmax; x++)
		{
			int i = x + y * grid.width;
			if (i < 0 || i > arrayMax) return CollisionResult(false); // Ensure you cant check outside array

			TileType tileType = grid.tiles[i];

			switch (tileType)
			{
			case TileType::Empty:
				break;

			case TileType::Solid:
				return CollisionResult(true);

			case TileType::Passthrough:
				if ((y * tileSize > static_cast<int>(prevP2.y)))
					return CollisionResult(true);
				else break;
			}
		}
	}

	// Slopeleft check, don't want to iterate over every overlapped tile, only the bottomright-most tile
	int bottomRightTile = xmax + ymax * grid.width;
	if (grid.tiles[bottomRightTile] == TileType::SlopeLeft)
	{
		// only need to check the rightmost corner of the rect
		relRightX = p2.x - xmax * tileSize;
		relRightY = p2.y - ymax * tileSize;
		if (relRightX + relRightY + 2 >= tileSize) // Why do we need +2 here for it to align correctly?
		{
			float2 resolvedPos = float2(pos.x, (ymax * tileSize) + tileSize - relRightX - (rectCol.GetSize().y / 2) - 3); // -3 here
			return CollisionResult(true, resolvedPos);
		}
	}

	int bottomLeftTile = xmin + ymax * grid.width;
	if (grid.tiles[bottomLeftTile] == TileType::SlopeRight)
	{
		// only need to check the lefttmost corner of the rect
		relLeftX = p1.x - xmin * tileSize;
		relLeftY = p2.y - ymax * tileSize;
		if (relLeftY >= relLeftX)
		{
			float2 resolvedPos = float2(pos.x, ymax * tileSize) + relLeftX - tileSize - (rectCol.GetSize().y / 2);
			return CollisionResult(true, resolvedPos);
		}
	}


	// Highlight the bottom right overlapped tile
	//float2 offset = Central::camera->pos;
	//Central::surface->Box(xmax * tileSize - offset.x, ymax * tileSize - offset.y, xmax * tileSize + tileSize - offset.x, ymax * tileSize + tileSize - offset.y, 0x00FF00);


	return false;
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






