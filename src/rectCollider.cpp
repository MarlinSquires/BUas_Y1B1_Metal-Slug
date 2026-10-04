#include "precomp.h"
#include "collisionSystem.h"
#include "rectCollider.h"
#include "central.h"



// Structors
RectCollider::RectCollider(CollisionLayerType layer, Tmpl8::Sprite* sprite, float2 scale) : Collider(ColliderType::Rect, layer), _scale(scale)
{
	_size.x = (float)sprite->GetWidth();
	_size.y = (float)sprite->GetHeight();
}

RectCollider::RectCollider(CollisionLayerType layer, Tmpl8::float2 size, float2 scale) : Collider(ColliderType::Rect, layer), _size(size), _scale(scale){}




// Lifecycle
void RectCollider::Start()
{
	UpdateRect(gameObject->GetWorldPos());// Idk if it actually matters whether this runs in Start() or only in first Tick()
}

void RectCollider::Tick()
{
	Collider::Tick();
	UpdateRect(gameObject->GetWorldPos());
}



void RectCollider::SetScale(float xScale, float yScale)
{
	_scale.x = xScale;
	_scale.y = yScale;
}



void RectCollider::UpdateRect(float2 pos)
{
	_p1.x = pos.x - (_size.x * _scale.x) / 2;
	_p1.y = pos.y - (_size.y * _scale.y) / 2;
	_p2.x = pos.x + (_size.x * _scale.x) / 2;
	_p2.y = pos.y + (_size.y * _scale.y) / 2;
}

