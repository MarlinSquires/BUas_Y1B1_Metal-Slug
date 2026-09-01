#include "renderSystem.h"

#include "spriteRenderer.h"

using namespace std;


void RenderLayer::Insert(SpriteRenderer rend)
{
	layer[count++] = rend;
}

void RenderLayer::Iterate()
{
	for (int i = 0; i < count; i++)
	{
		SpriteRenderer rend = layer[i];
		if (!rend.active) continue;
		rend.Tick();
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

void RenderSystem::Register(int layer, SpriteRenderer* spr)
{
	//layers[layer]->insert(spr);
}

void RenderSystem::Deregister(int layer, SpriteRenderer* spr)
{
	//layers[layer]->erase(spr);
}