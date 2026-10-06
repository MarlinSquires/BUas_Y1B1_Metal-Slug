#include "precomp.h"
#include "grid.h"
#include "gridCollider.h"
#include "gridRenderer.h"

#include "central.h"
#include "renderSystem.h"
#include "animationTypes.h"


GridRenderer::GridRenderer(GridCollider* gridCollider) : 
	SpriteRenderer(RenderLayerType::Debug, AnimationClipName::Tileset),grid(gridCollider->GetGrid()){};


// I should add bounds checking here - a full grid reduces FPS from 3000 to 1000
// Should I?
void GridRenderer::Render()
{
	int tileSize = grid.tileSize;
	int gridWidth = grid.width;

	float2 camPos = Central::camera->GetWorldPos();
	for (int y = 0; y < grid.height; y++)
	{
		for (int x = 0; x < gridWidth; x++)
		{
			TileType tileType = grid.tiles[x + y * gridWidth];
			if (tileType != TileType::Empty)
			{
				sprite->DrawFrame(surface, x * tileSize - camPos.x, y * tileSize - camPos.y, static_cast<char>(tileType) - 1); // Minus 1 because Tiled uses 1-5, whereas the frame data uses 0-4
			}
		}
	}
}
