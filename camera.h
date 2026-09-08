#pragma once
#include "component.h"

class GameObject;


class Camera : public Component
{

public:


	void Start() override;
	void Tick() override;

	void SetTarget(GameObject* go);

	Camera();


private:

	GameObject* target = nullptr;

	void FollowTarget();
	
};

