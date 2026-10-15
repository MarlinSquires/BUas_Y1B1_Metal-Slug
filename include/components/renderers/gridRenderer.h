#pragma once
#include "spriteRenderer.h"

class GridCollider;
struct Grid;
enum class RenderLayerName : uint8_t;


class GridRenderer : public SpriteRenderer
{

public:

	void Tick() override; // override and leave empty so it doesn't run SpriteRenderers Tick()
	void Render() override;

	GridRenderer(GridCollider* gridCollider);

private:

	Grid& grid;
};

