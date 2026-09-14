#include "precomp.h"
#include "grid.h"
#include "gridRenderer.h"
#include "central.h"


GridRenderer::GridRenderer(int layer, Grid* g) : Renderer(layer), 
grid(g), tileSize(grid->tileSize), gridWidth(grid->width),
gridHeight(grid->height), tileCount(gridWidth* gridHeight) {};



void GridRenderer::Render()
{
	float2 cpos = Central::camera->pos;
	for (int y = 0; y < gridHeight; y++)
	{
		for (int x = 0; x < gridWidth; x++)
		{
			if (grid->tiles[x + y * gridWidth])
			{
				Central::surface->Box(x * tileSize - cpos.x, y * tileSize - cpos.y, x * tileSize + tileSize - cpos.x, y * tileSize + tileSize - cpos.y, 0xFF0000);
			}
		}
	}
}
