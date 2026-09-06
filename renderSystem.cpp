#include "precomp.h"


#include "spriteRenderer.h"
#include "renderSystem.h"




void RenderLayer::Iterate()
{
	for (int i = 0; i < count; i++)
	{
		SpriteRenderer* rend = layer[i];
		//if (!rend->active) continue;
		rend->Tick();
	}
}



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
	for (RenderLayer* layer : layers)
	{
		layer->Iterate();
	}
}

void RenderSystem::Register(LayerType layer, SpriteRenderer* spr)
{
	RenderLayer* rend = layers[layer];
	rend->layer[rend->count++] = spr;
}

void RenderSystem::Deregister(LayerType layerIndex, int index)
{
	RenderLayer* layer = layers[layerIndex];

	layer[index] = layer[layer->count--]; // Will this cause UB? array is being iterated over by renderSystem, while the index is being replaced
}




