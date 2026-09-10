#pragma once
#include "renderer.h"
#include "grid.h"


class GridRenderer : public Renderer
{

private:

	Grid* grid;
	int tileSize;
	int gridWidth;
	int gridHeight;
	int tileCount;

public:

	void Render() override;

	GridRenderer(int layer, Grid* g);

	


};

