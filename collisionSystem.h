//#pragma once
//
//
//
//class CollisionSystem
//{
//public:
//
//	static int Register(int layer, Collider* col); // Returns index so collider can hold that info
//	static void Deregister(int layer, int index);
//
//	static bool Query(Collider& col, int layer, float2 ); // Checks for a collision against a layer, at a specific position
//
//
//private:
//	static CollisionLayer* layers[];
//
//};
//
//
//class CollisionLayer
//{
//
//public:
//
//	Collider* colliders[200] = {nullptr};
//	int colCount;
//
//};
//
