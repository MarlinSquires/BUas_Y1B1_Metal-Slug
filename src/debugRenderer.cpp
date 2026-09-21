#include "precomp.h"
#include "collider.h"
#include "debugRenderer.h"


DebugRenderer::DebugRenderer(RenderLayerType layer, Collider* col) : Renderer(layer), col(col){};

void DebugRenderer::Tick()
{
	if (col->overlapping) currentColour = overlapColour;
	else currentColour = normalColour;
}




