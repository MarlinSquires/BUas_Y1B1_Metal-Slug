#include "precomp.h"

#include "spriteRenderer.h"
#include "renderSystem.h"
#include "central.h"



void RenderLayer::Render()
{
	for (int i = 0; i < count; i++)
	{
		Renderer* rend = layer[i];
		if (!rend->active) continue;
		rend->Render();
	}
}


RenderLayer* RenderSystem::layers[5] = {};



RenderSystem::RenderSystem()
{
	for (int i = 0; i < 5; i++)
	{
		layers[i] = new RenderLayer();

	}
}


// Renders layers one after the other, ensuring layers with a higher
// index are drawn on top
void RenderSystem::Render()
{
	Central::surface->Clear(0x000000);
	for (RenderLayer* layer : layers)
	{
		layer->Render();
	}
}


void RenderSystem::Register(int layer, Renderer* spr)
{
	RenderLayer* rend = layers[layer];
	rend->layer[rend->count++] = spr;
}


void RenderSystem::Deregister(int layerIndex, int index)
{
	RenderLayer* layer = layers[layerIndex];

	layer[index] = layer[layer->count--]; // Will this cause UB? array is being iterated over by renderSystem, while the index is being replaced
}




