#pragma once
#include "renderer.h"
#include "renderSystem.h"

class TextRenderer : public Renderer
{
public:

	// Lifecycle
	void Render() override;

	// Setters
	void SetText(const char* text) { _text = text; };

	// Structors
	TextRenderer(const char* text = nullptr, int colour = 0xFFFFFF) : Renderer(RenderLayerName::Text), _text(text), _colour(colour) {};

private:

	const char* _text = nullptr;
	int _colour = 0xFFFFFF;

};
