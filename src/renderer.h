#pragma once
#include "component.h"


enum class RenderLayerType;

// Abstract base class for SpriteRenderer, RectRenderer, GridRenderer, and TextRenderer
class Renderer : public Component
{
public:

	virtual void Render() = 0;

	Tmpl8::Surface* GetSurface() { return surface; }

	Renderer(RenderLayerType layer);
	~Renderer();

protected:

	Tmpl8::Surface* surface;
	GameObject* camera;

	RenderLayerType layer;
	int index; // index in layer. Used when removing self from layer array

};

