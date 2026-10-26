#pragma once
#include "component.h"

class RectCollider;

class Prisoner : public Component
{
public:

	void Start() override;
	void Tick() override;

private:

	RectCollider* _col = nullptr;


};