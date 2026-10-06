#pragma once
#include "renderer.h"
#include "renderSystem.h"

class TextRenderer : public Renderer
{
public:

	const char* text = nullptr;
	int colour = 0xFFFFFF;
	void Render() override;

	TextRenderer(const char* text = nullptr, int colour = 0xFFFFFF) : Renderer(RenderLayerType::Text), text(text), colour(colour) {};

};
