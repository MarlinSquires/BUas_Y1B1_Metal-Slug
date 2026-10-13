#pragma once
#include "debugRenderer.h"

class RectCollider;

class RectRenderer : public DebugRenderer
{
public:

	void Tick() override;
	void Render() override; // Bool set by gameObject

	RectRenderer(RectCollider* col);


private:
	int _currentColour = 0xFFFFFF;
	int _normalColour = 0xFF0000;
	int _overlapColour = 0x00FF00;
	RectCollider* col;


};

