#pragma once

class RectCollider;
class TileCollider;
class PixelCollider;

class CollisionSystem
{
public:

	static int Register(int layer, Collider* col); // Returns index so collider can hold that info
	static void Deregister(int layer, int index);

	static bool Query(Collider& col, int layer, float2 pos); // Checks for a collision against a layer, at a specific position

	static bool RectVsRect(const RectCollider& rectCol1, const RectCollider& rectCol2, float2 pos);
	static bool RectVsTile(const RectCollider& rectCol, const TileCollider& tileCol);
	static bool RectVsPixel(const RectCollider& rectCol, const PixelCollider& pixelCol);
	// We dont need TileVsTile collisions because tiles never move
	static bool PixelVsTile(const PixelCollider& pixelCol, const TileCollider& tileCol);
	static bool PixelVsPixel(const PixelCollider& pixelCol1, const PixelCollider& pixelCol2);

	



private:
	static CollisionLayer* layers[];

};


class CollisionLayer
{

public:

	Collider* colliders[256] = {nullptr};
	int colCount;

};

