#pragma once
#include "renderer.h"

// Renderer should always be added as component after the collider


class Collider;

class DebugRenderer : public Renderer
{

public:

	void Tick() override;

	DebugRenderer(RenderLayerType layer, Collider* col);


protected:

	int currentColour = 0xFFFFFF;
	Collider* col;

private:
	int normalColour = 0xFF0000;
	int overlapColour = 0x00FF00;

};