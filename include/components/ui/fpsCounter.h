#pragma once
#include "component.h"
#include "textConverter.h"

class TextRenderer;

class FpsCounter : public Component
{
public:

	// Lifecycle
	void Start() override;
	void Tick() override;

private:

	TextRenderer* _rend = nullptr;
	TextConverter _converter;

	int _smoothedFPS = 1;
	float _smoothing = 100; // Higher means smoother FPS, but less precise

};