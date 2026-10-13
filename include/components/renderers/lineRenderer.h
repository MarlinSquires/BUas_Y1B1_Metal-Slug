#pragma once
#include "renderers/debugRenderer.h"

class LineRenderer : public DebugRenderer
{
public:

	void Render() override;
	void SetLine(float2 p1, float2 p2);

	LineRenderer();

private:

	float2 _p1 = {};
	float2 _p2 = {};

};
