#pragma once
#include "renderer.h"

// Renderer should always be added as component after the collider
// Draws origin


class Collider;

class DebugRenderer : public Renderer
{

public:

	// Lifecycle
	void Render() override;

	// Structors
	DebugRenderer(RenderLayerName layer);

protected:

	int colour = 0xFFFFFF;


};