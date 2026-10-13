#pragma once


class Rigidbody;


class AccelMove
{
public:
	void Move(Rigidbody& rb, char moveDir, float accel, float decel, float minSpeed, float maxSpeed);

};