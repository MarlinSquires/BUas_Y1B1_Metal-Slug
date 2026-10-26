#include "precomp.h"
#include "prisoner.h"
#include "rectCollider.h"
#include "collisionSystem.h"

void Prisoner::Start()
{
	_col = _gameObject->GetComponent<RectCollider>();

}


void Prisoner::Tick()
{
	if (_col->CollideWith(CollisionLayerName::Bullets, _gameObject->GetWorldPos()).collided)
	{
		_gameObject->MarkForDestruction();
	}
}


