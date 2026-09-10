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
	gameObject->pos.x = target->pos.x - Central::screenWidth / 2;
	gameObject->pos.y = target->pos.y - Central::screenHeight / 2;
}
