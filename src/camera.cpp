#include "precomp.h"
#include "camera.h"
#include "gameObject.h"
#include "central.h"




Camera::Camera()
{
	Central::camera = this->gameObject;
}

void Camera::Start()
{
	Central::camera = this->gameObject;
}

void Camera::Tick()
{
	FollowTarget();
}

void Camera::SetTarget(GameObject* go)
{
	target = go;
}

void Camera::FollowTarget()
{
	float2 newPos = 
	{ 
		target->GetWorldPos().x - Central::screenWidth / 2, 
		target->GetWorldPos().y - Central::screenWidth / 2
	};

	gameObject->SetPos(newPos);
}
