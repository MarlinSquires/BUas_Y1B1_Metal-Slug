#include "precomp.h"
#include "collisionSystem.h"
#include "colliders/rectCollider.h"
#include "renderers/spriteRenderer.h"
#include "central.h"



// Structors
RectCollider::RectCollider(CollisionLayerName layer, Sprite* sprite, float2 scale)
	: Collider(ColliderType::Rect, layer), _scale(scale)
{
	_size.x = (float)sprite->GetWidth();
	_size.y = (float)sprite->GetHeight();
}

RectCollider::RectCollider(CollisionLayerName layer, float2 size, float2 scale)
	: Collider(ColliderType::Rect, layer), _size(size), _scale(scale){}




// Lifecycle
void RectCollider::Start()
{
	UpdateRect();// Idk if it actually matters whether this runs in Start() or only in first Tick()

	if (_size.magnitude() == 0.0f)
	{
		_size.x = (float)GetGameObject()->GetComponent<SpriteRenderer>()->GetSprite()->GetWidth();
		_size.y = (float)GetGameObject()->GetComponent<SpriteRenderer>()->GetSprite()->GetHeight();
	}

}

void RectCollider::Tick()
{
	Collider::Tick();
	UpdateRect();
}


// Getters

float2 RectCollider::GetP1(float2 pos) const
{
	return float2(
		pos.x + _offset.x - (_size.x * _scale.x / 2), 
		pos.y + _offset.y - (_size.y * _scale.y / 2)
	);
}

float2 RectCollider::GetP2(float2 pos) const
{
	return float2(
		pos.x + _offset.x + (_size.x * _scale.x / 2),
		pos.y + _offset.y + (_size.y * _scale.y / 2)
	);
}


// Setters
void RectCollider::SetSize(float xSize, float ySize)
{ 
	if (xSize < 0 || ySize < 0) return;
	_size.x = xSize;
	_size.y = ySize;
}

void RectCollider::SetSize(Sprite* spr)
{
	_size.x = (float)spr->GetWidth();
	_size.y = (float)spr->GetHeight();
}


void RectCollider::SetScale(float xScale, float yScale)
{
	_scale.x = xScale;
	_scale.y = yScale;
}

void RectCollider::SetOffset(float xOffset, float yOffset)
{
	_offset.x = xOffset;
	_offset.y = yOffset;
}






void RectCollider::UpdateRect()
{
	float2 pos = GetGameObject()->GetWorldPos();
	_p1.x = pos.x + _offset.x - (_size.x * _scale.x / 2);
	_p1.y = pos.y + _offset.y - (_size.y * _scale.y / 2);

	_p2.x = pos.x + _offset.x + (_size.x * _scale.x / 2);
	_p2.y = pos.y + _offset.y + (_size.y * _scale.y / 2);
}

