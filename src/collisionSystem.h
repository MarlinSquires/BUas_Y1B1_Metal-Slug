#pragma once

class Collider;
class RectCollider;
class GridCollider;
class PixelCollider;



enum class CollisionLayerType
{
	Tiles,
	Player,
	Enemies,
	Bullets // Nothing should check against this layer, its just there to hold bullets, which will either check against player or enemy layers
};

struct CollisionLayer
{
	Collider* colliders[256] = { nullptr };
	int colCount = 0;
};


class CollisionSystem
{
public:

	static int Register(const CollisionLayerType layer, Collider* col); // Returns index so collider can hold that info
	static void Deregister(const CollisionLayerType layer, const int index);

	static bool Query(Collider* col, const CollisionLayerType layer, const float2 pos); // Checks for a collision against a layer, at a specific position

	static bool RectVsRect(RectCollider& rectCol1, RectCollider& rectCol2, const float2 pos);
	static bool RectVsTile(RectCollider& rectCol, GridCollider& tileCol, const float2 pos);
	static bool RectVsPixel(RectCollider& rectCol, PixelCollider& pixelCol, float2 pos);
	// We dont need TileVsTile collisions because tiles never move
	static bool PixelVsTile(PixelCollider& pixelCol, GridCollider& tileCol, float2 pos);
	static bool PixelVsPixel(PixelCollider& pixelCol1, PixelCollider& pixelCol2, float2 pos);


	// For AABB collision checking
	static bool CheckCollisionAxis(float aMin, float aMax, float bMin, float bMax);

	// Structors
	~CollisionSystem();



private:
	static const int arraySize = 4;
	static CollisionLayer collisionLayers[arraySize];

};







