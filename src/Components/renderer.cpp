#include "precomp.h"
#include "renderSystem.h"
#include "renderer.h"




Renderer::Renderer(RenderLayerType renderLayer)
{
	// Set renderLayer
	RenderSystem::Register(renderLayer, this);
	layer = renderLayer;
	index = RenderSystem::GetLayer(renderLayer).count;



}

Renderer::~Renderer()
{
	RenderSystem::Deregister(layer, index);
}
