#include "precomp.h"
#include "collisionSystem.h"
#include "rectCollider.h"
#include "central.h"



// Structors
RectCollider::RectCollider(CollisionLayerType layer, Tmpl8::Sprite* sprite) : Collider(ColliderType::Rect, layer)
{
	size.x = (float)sprite->GetWidth();
	size.y = (float)sprite->GetHeight();
}

RectCollider::RectCollider(CollisionLayerType layer, Tmpl8::float2 size) : Collider(ColliderType::Rect, layer), size(size){}




// Lifecycle
void RectCollider::Start()
{
	UpdateRect(gameObject->pos);// Idk if it actually matters whether this runs in Start() or only in first Tick()
}

void RectCollider::Tick()
{
	Collider::Tick();
	UpdateRect(gameObject->pos);
	CollideWith(CollisionLayerType::Player, gameObject->pos);
}



void RectCollider::UpdateRect(float2 pos)
{
	//p1.x = round(pos.x - size.x / 2); // Do I need this rounding for the collision calculations? It makes the rectRenderers look jittery
	//p1.y = round(pos.y - size.y / 2);
	//p2.x = round(pos.x + size.x / 2);
	//p2.y = round(pos.y + size.y / 2);

	p1.x = pos.x - size.x / 2;
	p1.y = pos.y - size.y / 2;
	p2.x = pos.x + size.x / 2;
	p2.y = pos.y + size.y / 2;
}



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
