#include "precomp.h"
#include "grid.h"
#include "colliders/gridCollider.h"
#include "renderers/gridRenderer.h"

#include "central.h"
#include "renderSystem.h"
#include "animationTypes.h"


GridRenderer::GridRenderer(GridCollider* gridCollider) : 
	SpriteRenderer(RenderLayerName::Debug, AnimationClipName::Tileset), 
	grid(gridCollider->GetGrid()){};




void GridRenderer::Tick()
{
	Renderer::Tick();
}




void GridRenderer::Render()
{
	if (!debug) return;


	int tileSize = grid.tileSize;
	int gridWidth = grid.width;

	for (int y = 0; y < grid.height; y++)
	{
		for (int x = 0; x < gridWidth; x++)
		{
			TileType tileType = grid.tiles[x + y * gridWidth];
			if (tileType != TileType::Empty)
			{
				sprite->DrawFrame(surface, (int)(x * tileSize - camOffset.x), (int)(y * tileSize - camOffset.y), static_cast<char>(tileType) - 1); // Minus 1 because Tiled uses 1-5, whereas the frame data uses 0-4
			}
		}
	}
}
