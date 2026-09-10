#include "precomp.h"
//#include "collider.h"
//#include "collisionSystem.h"
//
//
//
//CollisionLayer* CollisionSystem::layers[] = {
//	new CollisionLayer(),
//	new CollisionLayer(),
//	new CollisionLayer(),
//	new CollisionLayer(),
//	new CollisionLayer(),
//
//};
//
//
//int CollisionSystem::Register(int layer, Collider* col)
//{
//	CollisionLayer* l = layers[layer];
//	l->colliders[l->colCount++] = col;
//	return l->colCount - 1;
//}
//
//void CollisionSystem::Deregister(int layer, int index)
//{
//	CollisionLayer* l = layers[layer];
//	l->colliders[index] = l->colliders[l->colCount--];
//}
//
//
//bool CollisionSystem::Query(Collider& col, int layer, float2 pos)
//{
//	CollisionLayer* l = layers[layer];
//	Collider** c = l->colliders;
//
//	// Cache pos
//	float2 originalPos = col.gameObject->pos;
//
//	for (int i = 0; i < l->colCount; i++)
//	{
//		if (!c[i]->active) continue;
//		// Move rect to check position
//		col.UpdateRect(pos);
//
//		const float2 colP1 = c[i]->GetP1(); // float2 and pointer are both 8 bytes, so does it matter whther I pass by value or ptr / ref?
//		const float2 colP2 = c[i]->GetP2(); // Pass by pointer would cause more cache misses ??
//
//		// AABB logic
//		bool xCollision = CheckCollisionAxis(col.GetP1().x, col.GetP2().x, colP1.x, colP2.x);
//		bool yCollision = CheckCollisionAxis(col.GetP1().y, col.GetP2().y, colP1.y, colP2.y);
//
//		// Move rect back
//		col.UpdateRect(originalPos);
//
//
//		if (xCollision && yCollision)
//		{
//			//cout << "I'm colliding!!!" << endl;
//			return true;
//		}
//	}
//
//	return false;
//}
//
//
//bool CheckCollisionAxis(float aMin, float aMax, float bMin, float bMax)
//{
//	return aMin < bMax && aMax > bMin;
//}
//
//
//
//
//
//
