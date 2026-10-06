#include "precomp.h"

#include "spriteRenderer.h"
#include "renderSystem.h"
#include "central.h"




void RenderLayer::Render()
{
	for (int i = 0; i < count; i++)
	{
		Renderer* rend = renderers[i];
		if (!rend->active) continue;
		rend->Render();
	}
}


RenderLayer& RenderSystem::GetLayer(RenderLayerType layer)
{
	return layers[static_cast<int>(layer)];
}


// Renders layers one after the other, ensuring layers with a higher
// index are drawn on top
void RenderSystem::Render()
{
	Central::surface->Clear(0x000000);
	for (RenderLayer& layer : layers)
	{
		layer.Render();
	}
}


void RenderSystem::Register(RenderLayerType layerIndex, Renderer* spr)
{
	RenderLayer& rend = layers[static_cast<int>(layerIndex)];
	rend.renderers[rend.count++] = spr;
}


void RenderSystem::Deregister(RenderLayerType layerIndex, int index)
{
	RenderLayer& layer = layers[static_cast<int>(layerIndex)];

	layer.renderers[index] = layer.renderers[layer.count--]; // Will this cause UB? array is being iterated over by renderSystem, while the index is being replaced
}




