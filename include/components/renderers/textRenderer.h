#pragma once
#include "renderer.h"
#include "renderSystem.h"

class TextRenderer : public Renderer
{
public:

	// Lifecycle
	void Render() override;

	// Structors
	TextRenderer(const char* text = nullptr, int colour = 0xFFFFFF) : Renderer(RenderLayerName::Text), text(text), colour(colour) {};


	const char* text = nullptr;
	int colour = 0xFFFFFF;

};
