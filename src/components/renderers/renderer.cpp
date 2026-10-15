#include "precomp.h"
#include "renderSystem.h"
#include "renderers/renderer.h"
#include "central.h"



Renderer::Renderer(RenderLayerName renderLayer)
{
	// Set renderLayer
	RenderSystem::Register(renderLayer, this);
	layer = renderLayer;
}

Renderer::~Renderer()
{
	RenderSystem::Deregister(layer, index);
}


void Renderer::Tick() // Calc camOffset for all renderers
{
	float2 camPos = Central::camera->GetWorldPos();
	camOffset = float2(camPos.x - SCRWIDTH / 2, camPos.y - SCRHEIGHT / 2);
}

