#pragma once

#include "gameObject.h"


class Component // Abstract class
{
	friend class GameObject;

public:
	
	// Lifecycle
	virtual void Start() {};
	virtual void PostStart() {};
	virtual void Tick() {};

	// Getters
	GameObject* GetGameObject() const { return _gameObject; }

	// Structors
	virtual ~Component() = 0;


	bool active = true;
	bool debug = false;


protected:

	GameObject* _gameObject = nullptr;

};

inline Component::~Component() = default; // Defining it inline here means I don't need a component.cpp file
