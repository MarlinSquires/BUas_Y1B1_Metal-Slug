#include "precomp.h"
#include "renderers/lineRenderer.h"
#include "central.h"
#include "renderSystem.h"


LineRenderer::LineRenderer() : DebugRenderer(RenderLayerName::Debug) {};


void LineRenderer::Render()
{
	float2 camOffset = Central::camera->GetWorldPos();

	Central::surface->Line(
		_p1.x - camOffset.x, _p1.y - camOffset.y, 
		_p2.x - camOffset.x, _p2.y - camOffset.y, 
		colour);
}


void LineRenderer::SetLine(float2 p1, float2 p2)
{
	_p1 = p1;
	_p2 = p2;
}



