#include "precomp.h"
#include "renderSystem.h"
#include "renderers/renderer.h"




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
