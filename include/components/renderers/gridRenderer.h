#pragma once
#include "spriteRenderer.h"

class GridCollider;
struct Grid;
enum class RenderLayerName : uint8_t;


class GridRenderer : public SpriteRenderer
{

public:

	void Render() override;

	GridRenderer(GridCollider* gridCollider);

private:

	Grid& grid;
};

