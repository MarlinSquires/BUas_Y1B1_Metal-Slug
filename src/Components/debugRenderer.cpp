#include "precomp.h"
#include "collider.h"
#include "debugRenderer.h"
#include "central.h"


DebugRenderer::DebugRenderer(RenderLayerType layer, Collider* col) : Renderer(layer), col(col){};

void DebugRenderer::Tick()
{
	if (col->overlapping) currentColour = overlapColour;
	else currentColour = normalColour;
}

void DebugRenderer::Render()
{
	if (!gameObject->debug) return;
	float2 offset = Central::camera->GetWorldPos();
	float2 screenPos = gameObject->GetWorldPos() - offset;

	Central::surface->Box(
		(int)round(screenPos.x - 2), // Rounding keeps box size consistent - truncation causes jitter
		(int)round(screenPos.y - 2),
		(int)round(screenPos.x + 2),
		(int)round(screenPos.y + 2),
		0xFF0000);

}




