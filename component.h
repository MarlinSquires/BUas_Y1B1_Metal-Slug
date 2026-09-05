#pragma once


class GameObject;

class Component // Abstract class
{
public:

	GameObject* gameObject; // Pointer instead of ref so I don't need to pass go in constructor, would add extra boilerplate
	bool active = true;

	virtual void Start();
	virtual void Tick();

	virtual ~Component() = 0;
};

