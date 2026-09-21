#pragma once
#include "debugRenderer.h"

class RectCollider;

class RectRenderer : public DebugRenderer
{
public:
	void Render() override; // Bool set by gameObject

	RectRenderer(RectCollider* col);


private:
	RectCollider* col;

};

