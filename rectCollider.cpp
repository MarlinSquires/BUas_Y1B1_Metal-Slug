#include "precomp.h"
#include "rectCollider.h"
#include "central.h"



bool RectCollider::CollideWith(const Collider* other)
{
	return other->RectCollide(this);
}

// Structors
RectCollider::RectCollider(int layer, Tmpl8::Sprite* sprite) : Collider(layer)
{
	size.x = (float)sprite->GetWidth();
	size.y = (float)sprite->GetHeight();
}

RectCollider::RectCollider(int layer, Tmpl8::float2 size) : Collider(layer), size(size){}




void RectCollider::Start()
{
	UpdateRect(gameObject->pos);// Idk if it actually matters whether this runs in Start() or only in first Tick()
}

void RectCollider::Tick()
{
	Collider::Tick();
	UpdateRect(gameObject->pos);
}



//Collider* RectCollider::CollideWith(const float2 pos, Collider* col)
//{
//	//if (!col->active) return nullptr;
//	//// Cache pos
//	//float2 originalPos = gameObject->pos;
//
//	//// Move rect to check position
//	//UpdateRect(pos);
//
//	//const float2 colP1 = col->GetP1(); // float2 and pointer are both 8 bytes, so does it matter whther I pass by value or ptr / ref?
//	//const float2 colP2 = col->GetP2(); // Pass by pointer would cause more cache misses ??
//
//	//// AABB logic
//	//bool xCollision = CheckCollisionAxis(p1.x, p2.x, colP1.x, colP2.x);
//	//bool yCollision = CheckCollisionAxis(p1.y, p2.y, colP1.y, colP2.y);
//
//	//// Move rect back
//	//UpdateRect(originalPos);
//
//	//if (xCollision && yCollision) return col;
//	//else return nullptr;
//};

//
//Collider* RectCollider::CollideWith(Tmpl8::float2 pos, std::string layer)
//{
//
//	//// Cache pos
//	//float2 originalPos = gameObject->pos;
//
//	//for (auto& col : collisionSystem->GetLayer(layer))
//	//{
//	//	if (!col->active) continue;
//	//	// Move rect to check position
//	//	UpdateRect(pos);
//
//	//	const float2 colP1 = col->GetP1(); // float2 and pointer are both 8 bytes, so does it matter whther I pass by value or ptr / ref?
//	//	const float2 colP2 = col->GetP2(); // Pass by pointer would cause more cache misses ??
//
//	//	// AABB logic
//	//	bool xCollision = CheckCollisionAxis(p1.x, p2.x, colP1.x, colP2.x);
//	//	bool yCollision = CheckCollisionAxis(p1.y, p2.y, colP1.y, colP2.y);
//
//	//	// Move rect back
//	//	UpdateRect(originalPos);
//
//
//	//	if (xCollision && yCollision)
//	//	{
//	//		//cout << "I'm colliding!!!" << endl;
//	//		return col;
//	//	}
//	//}
//	return nullptr;
//}




//void RectCollider::MoveAndCollide(string layer, float2 distance)
//{
//	//float2& pos = gameObject->pos;
//
//	//auto& colliders = collisionSystem->GetLayer(layer);
//
//	//float2 targetPos = pos + distance;
//	//int xMoveSign = utils::sign(distance.x);
//	//int yMoveSign = utils::sign(distance.y);
//
//	//bool xCollide = false;
//	//bool yCollide = false;
//
//	//// Check for collisions against every collider in scene
//	//for (int i = 0; i < colliders.size(); i++)
//	//{
//	//	Collider* col = colliders[i];
//
//	//	for (int j = 0; j < abs(distance.x); j++)
//	//	{
//	//		xCollide = CollideAt(
//	//			float2(pos.x + (j + 1 * xMoveSign), pos.y),
//	//			col);
//
//	//		if (xCollide)
//	//		{
//	//			targetPos.x = (pos.x + (j)*xMoveSign);
//	//			break;
//	//		}
//	//	}
//
//	//	for (int j = 0; j < abs(distance.y); j++)
//	//	{
//	//		yCollide = CollideAt(
//	//			float2(pos.x, pos.y + (j + 1 * yMoveSign)),
//	//			col);
//
//	//		if (yCollide)
//	//		{
//	//			targetPos.y = (pos.y + (j)*yMoveSign);
//	//			break;
//	//		}
//	//	}
//	//}
//
//	//// Handle x and y separately
//	//pos.x = targetPos.x;
//
//	//pos.y = targetPos.y;
//}











void RectCollider::UpdateRect(float2 pos)
{
	p1.x = round(pos.x - size.x / 2);
	p1.y = round(pos.y - size.y / 2);
	p2.x = round(pos.x + size.x / 2);
	p2.y = round(pos.y + size.y / 2);
}


void RectCollider::DrawCollider()
{
	if (!gameObject->debug) return;

	if (Central::camera == nullptr) return;

	float2 offset = Central::camera->pos;

	Central::surface->Box(
		(int)round(p1.x - offset.x),
		(int)round(p1.y - offset.y),
		(int)round(p2.x - offset.x),
		(int)round(p2.y - offset.y),
		0xFF0000);
}


