#pragma once
#include "component.h"

class TextRenderer;

class FpsCounter : public Component
{
public:
	void Start() override;
	void Tick() override;


private:
	TextRenderer* rend = nullptr;

	char textBuffer[20];

	int smoothedFPS = 1;
	float smoothing = 100; // Higher means smoother FPS, but less precise

};