#pragma once
#include "debugRenderer.h"

class GridCollider;
class Grid;
enum class RenderLayerType;


class GridRenderer : public DebugRenderer
{

public:

	void Render() override;

	GridRenderer(GridCollider* gridCollider);

private:

	Grid* grid;
	int tileSize;
	int gridWidth;
	int gridHeight;
	int tileCount;

};

