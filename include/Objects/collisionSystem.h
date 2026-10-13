#pragma once

class Collider;
class RectCollider;
class GridCollider;
class PixelCollider;



enum class CollisionLayerName : uint8_t
{
	Solids, // Non-moving colliders that block actors
	Player,
	Enemies,
	Triggers, // For stuff like enemy knife colliders
	Bullets, // Nothing should check against this layer, its just there to hold bullets, which will either check against player or enemy layers

	COUNT
};

struct CollisionResult
{
	float2 resolvedPos = { 0.0f, 0.0f };
	bool collided = false;
	const Collider* col = nullptr;
	
	CollisionResult(bool collided, float2 resolvedPos = { 0.0f, 0.0f }, Collider* col = nullptr) : collided(collided), resolvedPos(resolvedPos), col(col) {};
};

struct CollisionLayer
{
	static const int SIZE = 1024;
	Collider* colliders[SIZE] = { nullptr };
	int count = 0;
};


class CollisionSystem
{
public:

	static int Register(const CollisionLayerName layer, Collider* col); // Returns index so collider can hold that info
	static void Deregister(const CollisionLayerName layer, const int index);

	// result as the out parameter - used to optionally mutate the colliders position
	static CollisionResult Query(const Collider& col, const CollisionLayerName layer, const float2 pos); // Checks for a collision against a layer, at a specific position

	static CollisionResult RectVsRect(CollisionLayerName collisionLayer, const RectCollider& rectCol1, const RectCollider& rectCol2, const float2 pos);
	static CollisionResult RectVsTile(const RectCollider& rectCol, GridCollider& tileCol, const float2 pos);
	//static bool RectVsPixel(RectCollider& rectCol, PixelCollider& pixelCol, float2 pos);
	//// We dont need TileVsTile collisions because tiles never move
	//static CollisionResult PixelVsTile(PixelCollider& pixelCol, GridCollider& tileCol, float2 pos);
	//static CollisionResult PixelVsPixel(PixelCollider& pixelCol1, PixelCollider& pixelCol2, float2 pos);


	// For AABB collision checking
	static bool CheckCollisionAxis(float aMin, float aMax, float bMin, float bMax);


private:
	static inline CollisionLayer collisionLayers[static_cast<int>(CollisionLayerName::COUNT)];

};







