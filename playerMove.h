#pragma once
#include "component.h"


class PlayerMove : public Component
{

	void Tick() override;

	void UpdateInputs();


};

