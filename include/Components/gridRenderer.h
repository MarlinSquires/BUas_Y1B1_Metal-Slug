#pragma once
#include "spriteRenderer.h"

class GridCollider;
struct Grid;
enum class RenderLayerType;


class GridRenderer : public SpriteRenderer
{

public:

	void Render() override;

	GridRenderer(GridCollider* gridCollider);

private:

	Grid& grid;
};

