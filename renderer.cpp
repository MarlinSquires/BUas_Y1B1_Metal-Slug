#include "precomp.h"
#include "renderer.h"
#include "renderSystem.h"



Renderer::Renderer(int renderLayer)
{

	// Set renderLayer
	RenderSystem::Register(renderLayer, this);
	layer = renderLayer;
	index = RenderSystem::layers[layer]->count;

	 
}

Renderer::~Renderer()
{
	RenderSystem::Deregister(layer, index);
}
