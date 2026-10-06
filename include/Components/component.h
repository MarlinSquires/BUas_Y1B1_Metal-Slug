#pragma once

#include "gameObject.h"


class Component // Abstract class
{
public:

	GameObject* gameObject; 
	bool active = true;

	virtual void Start();
	virtual void PostStart();
	virtual void Tick();

	virtual ~Component() = 0;
};

