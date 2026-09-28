#include "precomp.h"
#include "collider.h"
#include "rectCollider.h"
#include "gridCollider.h"
#include "pixelCollider.h"
#include "collisionSystem.h"
#include "grid.h"


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


bool CollisionSystem::Query(Collider* collider, const CollisionLayerType collisionLayer, const float2 pos)
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
				if (RectVsRect(static_cast<RectCollider&>(col), static_cast<RectCollider&>(col2), pos)) return true;
			}
			else if (col2.GetType() == ColliderType::Tile)
			{
				if (RectVsTile(static_cast<RectCollider&>(col), static_cast<GridCollider&>(col2), pos)) return true;
			}
			else
			{
				if (RectVsPixel(static_cast<RectCollider&>(col), static_cast<PixelCollider&>(col2), pos)) return true;
			}
		}

		else // Don't need to check if type == pixel, because we only check two col1 types
		{
			if (col2.GetType() == ColliderType::Tile)
			{
				if (PixelVsTile(static_cast<PixelCollider&>(col), static_cast<GridCollider&>(col2), pos)) return true;
			}
			else if (col2.GetType() == ColliderType::Pixel)
			{
				if (PixelVsPixel(static_cast<PixelCollider&>(col), static_cast<PixelCollider&>(col2), pos)) return true;
			}
		}
	}
	return false;
}

	


bool CollisionSystem::RectVsRect(RectCollider& rectCol1, RectCollider& rectCol2, const float2 pos)
{
	if (!rectCol2.active) return false;

	float2 originalPos = rectCol1.gameObject->pos;

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
		return true;
	}
	
	// No collision found
	rectCol1.overlapping = false;
	rectCol2.overlapping = false;
	
	return rectCol1.overlapping;
}





bool CollisionSystem::RectVsTile(RectCollider& rectCol, GridCollider& tileCol, const float2 pos)
{

	float2 originalPos = rectCol.gameObject->pos;
	float2 prevP1 = rectCol.GetP1();
	float2 prevP2 = rectCol.GetP2();

	// Convert worldspace positions to gridspace
	rectCol.UpdateRect(pos);

	Grid& grid = tileCol.GetGrid();
	int tileSize = grid.tileSize;
	int arrayMax = grid.width * grid.height;

	float2 p1 = rectCol.GetP1();
	float2 p2 = rectCol.GetP2();

	int xmin = p1.x / tileSize;
	int ymin = p1.y / tileSize;
	
	int xmax = p2.x / tileSize;
	int ymax = p2.y / tileSize;

	rectCol.UpdateRect(originalPos);

	int relRightX = 0;
	int relRightY = 0;
	int relLeftX = 0;
	int relLeftY = 0;

	// Loop over all overlapping tiles positions and check for solidity
	for (int y = ymin; y <= ymax; y++)
	{
		for (int x = xmin; x <= xmax; x++)
		{
			int i = x + y * grid.width;
			if (i < 0 || i > arrayMax) return false; // Ensure you cant check outside array

			char val = grid.tiles[i];

			switch (val)
			{
			case 0: // Empty
				break;

			case 1: // Solid
				return true;
	
			case 2: // Passthrough
				if ((y * tileSize > static_cast<int>(prevP2.y)))
					return true;
				else break;
				
			case 3: // Slope left 
				// only need to check the rightmost corner of the rect
				relRightX = p2.x - x * tileSize;
				relRightY = p2.y - y * tileSize;
				if (relRightX + relRightY > tileSize) return true;
				else break;

			case 4: // Slope right
				// only need to check the leftmost corner of the rect
				relLeftX = p1.x - x * tileSize;
				relLeftY = p2.y - y * tileSize;
				if (relLeftX - relLeftY < tileSize) return true;
				else break;
			}
		}
	}

	return false;
}




bool CollisionSystem::CollisionSystem::RectVsPixel(RectCollider& rectCol, PixelCollider& pixelCol, float2 pos)
{

	return false;

}

bool CollisionSystem::PixelVsTile(PixelCollider& pixelCol, GridCollider& tileCol, float2 pos)
{

	return false;

}
bool CollisionSystem::PixelVsPixel(PixelCollider& pixelCol1, PixelCollider& pixelCol2, float2 pos)
{

	return false;


}





// For AABB collision checking
bool CollisionSystem::CheckCollisionAxis(float aMin, float aMax, float bMin, float bMax)
{
	return aMin < bMax && aMax > bMin;
}






