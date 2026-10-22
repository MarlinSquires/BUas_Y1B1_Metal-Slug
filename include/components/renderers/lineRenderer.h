#pragma once
#include "debugRenderer.h"

class LineRenderer : public DebugRenderer
{
public:

	// Lifecycle
	void Render() override;
	void SetLine(float2 p1, float2 p2);

	// Structors
	LineRenderer();

private:

	float2 _p1 = {};
	float2 _p2 = {};

};
