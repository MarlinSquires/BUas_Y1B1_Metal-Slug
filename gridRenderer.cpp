#include "precomp.h"
#include "grid.h"
#include "gridRenderer.h"
#include "central.h"


GridRenderer::GridRenderer(int layer, Grid* g) : Renderer(layer), 
grid(g), tileSize(grid->tileSize), gridWidth(grid->width),
gridHeight(grid->height), tileCount(gridWidth* gridHeight) {};



void GridRenderer::Render()
{
	int c = 0;
	for (int y = 0; y < gridHeight; y++)
	{
		for (int x = 0; x < gridWidth; x++)
		{
			if (grid->tiles[x + y * gridWidth])
			{
				c++;
			/*	printf("x: %d \n", x);
				printf("y: %d \n", y);
				printf("count: %d \n", c);*/
				Central::surface->Box(0, 0, 10, 10, 0xFF0000);
				//Central::surface->Box(x, y, x + tileSize, y + tileSize, 0xFF0000);
				//Central::surface->Box(x, y, x + tileSize, y + tileSize, 0xFF0000);
			}
		}
	}
}
