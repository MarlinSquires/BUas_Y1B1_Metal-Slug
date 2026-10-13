#include "precomp.h"
#include "central.h"
#include "colliders/rectCollider.h"
#include "renderers/rectRenderer.h"
#include "renderSystem.h"


RectRenderer::RectRenderer(RectCollider* col) : DebugRenderer(RenderLayerName::Debug), col(col) {};


void RectRenderer::Tick()
{
	assert(col != nullptr);

	if (col->Overlapping()) _currentColour = _overlapColour;
	else _currentColour = _normalColour;
}


void RectRenderer::Render()
{
	if (!GetGameObject()->debug) return;

	DebugRenderer::Render();

	float2 offset = Central::camera->GetWorldPos();

	Central::surface->Box(
		(int)round(col->GetP1().x - offset.x),
		(int)round(col->GetP1().y - offset.y),
		(int)round(col->GetP2().x - offset.x),
		(int)round(col->GetP2().y - offset.y),
		_currentColour);
}



