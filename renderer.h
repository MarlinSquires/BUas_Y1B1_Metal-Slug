#pragma once
#include "component.h"

// Abstract base class for SpriteRenderer, GridRenderer, and TextRenderer

class Renderer : public Component
{
public:

	virtual void Render() = 0;

	Renderer(int layer);
	~Renderer();

protected:

	Tmpl8::Surface* surface;
	GameObject* camera;

	int layer;
	int index; // index in layer. Used when removing self from layer array

};

