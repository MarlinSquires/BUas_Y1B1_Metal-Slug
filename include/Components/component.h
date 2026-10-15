#pragma once

#include "gameObject.h"


class Component // Abstract class
{
	friend class GameObject;

public:
	
	GameObject* GetGameObject() const { return _gameObject; }

	virtual void Start() {};
	virtual void PostStart() {};
	virtual void Tick() {};

	virtual ~Component() = 0;

	bool active = true;
	bool debug = false;


private:
	
	GameObject* _gameObject = nullptr;
};

inline Component::~Component() = default; // Defining it inline here means I don't need a component.cpp file
