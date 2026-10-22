#include "precomp.h"

#include "renderers/spriteRenderer.h"
#include "renderSystem.h"
#include "central.h"







RenderLayer& RenderSystem::GetLayer(RenderLayerName layer)
{
	return layers[static_cast<int>(layer)];
}



void RenderSystem::Render()
{
	Central::surface->Clear(0x99BBFF);
	for (RenderLayer& layer : layers)
	{
		layer.Render();
	}
}

void RenderLayer::Render()
{
	for (int i = 0; i < count; i++)
	{
		Renderer* rend = renderers[i];
		if (!rend->active) continue;
		rend->Render();
	}
}


void RenderSystem::Register(RenderLayerName layerIndex, Renderer* renderer)
{
	RenderLayer& layer = layers[static_cast<int>(layerIndex)];
	Renderer* rend = layer.renderers[layer.count++] = renderer;
	rend->index = layer.count - 1;
}


void RenderSystem::Deregister(RenderLayerName layerIndex, const int index)
{
	RenderLayer& layer = layers[static_cast<int>(layerIndex)];
	assert(index >= 0 && index < layer.count);

	layer.renderers[index] = layer.renderers[--layer.count];
	layer.renderers[index]->index = index;
	layer.renderers[layer.count] = nullptr;
}




