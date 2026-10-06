#include "precomp.h"
#include "central.h"
#include "rectCollider.h"
#include "rectRenderer.h"
#include "renderSystem.h"


RectRenderer::RectRenderer(RectCollider* col) : DebugRenderer(RenderLayerType::Debug, col), col(col) {};


void RectRenderer::Render()
{
	if (!gameObject->debug) return;

	DebugRenderer::Render();

	float2 offset = Central::camera->GetWorldPos();

	Central::surface->Box(
		(int)round(col->GetP1().x - offset.x),
		(int)round(col->GetP1().y - offset.y),
		(int)round(col->GetP2().x - offset.x),
		(int)round(col->GetP2().y - offset.y),
		currentColour);

	//float p1x = col->GetP1().x;
	//float p1y = col->GetP1().y;
	//float p2x = col->GetP2().x;
	//float p2y = col->GetP2().y;


	//Central::surface->Box(
	//	p1x - offset.x,
	//	p1y - offset.y,
	//	p2x - offset.x,
	//	p2y - offset.y,
	//	colour);

}



