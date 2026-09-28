#include "precomp.h"
#include "grid.h"
#include "gridCollider.h"
#include "gridRenderer.h"

#include "central.h"
#include "renderSystem.h"
#include "spriteFactory.h"


GridRenderer::GridRenderer(GridCollider* gridCollider) : SpriteRenderer(RenderLayerType::Debug, SpriteType::Tileset),
grid(gridCollider->GetGrid()){};


// I should add bounds checking here - a full grid reduces FPS from 3000 to 1000
// Should I?
void GridRenderer::Render()
{
	int tileSize = grid.tileSize;
	int gridWidth = grid.width;

	float2 camPos = Central::camera->pos;
	for (int y = 0; y < grid.height; y++)
	{
		for (int x = 0; x < gridWidth; x++)
		{
			char val = grid.tiles[x + y * gridWidth];
			if (val)
			{
				sprite->DrawFrame(surface, x * tileSize - camPos.x, y * tileSize - camPos.y, val - 1); // Minus 1 because Tiled uses 1-5, whereas the frame data uses 0-4
			}
		}
	}
}
