#pragma once
#include "component.h"


enum class RenderLayerName : uint8_t;

// Abstract base class for SpriteRenderer, RectRenderer, GridRenderer, and TextRenderer
class Renderer : public Component
{
public:

	void Tick() override;
	virtual void Render() = 0;

	// Getters
	Surface* GetSurface() { return surface; }
	

	// Structors
	Renderer(RenderLayerName layer);
	~Renderer();

	int index; // index in layer. Used when removing self from layer array

protected:

	float2 camOffset = {};

	Surface* surface;
	GameObject* camera;

	RenderLayerName layer;
	

};

