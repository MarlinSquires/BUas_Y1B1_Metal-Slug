#pragma once
#include "component.h"


enum class RenderLayerName : uint8_t;

// Abstract base class for SpriteRenderer, RectRenderer, GridRenderer, and TextRenderer
class Renderer : public Component
{
public:

	virtual void Render() = 0;

	Tmpl8::Surface* GetSurface() { return surface; }

	Renderer(RenderLayerName layer);
	~Renderer();

	int index; // index in layer. Used when removing self from layer array

protected:

	Tmpl8::Surface* surface;
	GameObject* camera;

	RenderLayerName layer;
	

};

