#include "precomp.h"
#include "central.h"
#include "colliders/rectCollider.h"
#include "renderers/rectRenderer.h"
#include "renderSystem.h"


RectRenderer::RectRenderer(RectCollider* col) : DebugRenderer(RenderLayerName::Debug), col(col) {};


void RectRenderer::Tick()
{
	Renderer::Tick();
	assert(col != nullptr);

	if (col->Overlapping()) _currentColour = _overlapColour;
	else _currentColour = _normalColour;
}


void RectRenderer::Render()
{
	DebugRenderer::Render();
	if (!debug) return;

	Central::surface->Box(
		(int)round(col->GetP1().x - camOffset.x),
		(int)round(col->GetP1().y - camOffset.y),
		(int)round(col->GetP2().x - camOffset.x),
		(int)round(col->GetP2().y - camOffset.y),
		_currentColour);
}



