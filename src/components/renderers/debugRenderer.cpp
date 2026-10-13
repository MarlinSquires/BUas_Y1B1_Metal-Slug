#include "precomp.h"
#include "colliders/collider.h"
#include "renderers/debugRenderer.h"
#include "central.h"


DebugRenderer::DebugRenderer(RenderLayerName layer) : Renderer(layer){};



void DebugRenderer::Render() // Renders object origin
{
	if (!GetGameObject()->debug) return;
	float2 screenPos = GetGameObject()->GetWorldPos() - Central::camera->GetWorldPos();

	Central::surface->Box(
		(int)round(screenPos.x - 2), // Rounding keeps box size consistent - truncation causes jitter
		(int)round(screenPos.y - 2),
		(int)round(screenPos.x + 2),
		(int)round(screenPos.y + 2),
		colour);
}




