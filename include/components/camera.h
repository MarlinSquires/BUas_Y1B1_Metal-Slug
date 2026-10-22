#pragma once
#include "component.h"

class GameObject;


class Camera : public Component
{

public:

	// Lifecycle
	void Start() override;
	void Tick() override;

	// Setters
	void SetTarget(GameObject* go);

	// Structors
	Camera();


private:

	GameObject* target = nullptr;

	void FollowTarget();
	
};

