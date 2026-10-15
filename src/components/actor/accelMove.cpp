#include "precomp.h"
#include "accelMove.h"
#include "rigidbody.h"
#include "central.h"



void AccelMove::Move(Rigidbody& rb, char moveDir, float accel, float decel, float minSpeed, float maxSpeed)
{

	float& xVel = rb.velocity.x;

	if (moveDir != 0 && abs(xVel) < minSpeed) // Start off at minSpeed
		xVel = moveDir * minSpeed;
	else if (moveDir != 0)
		rb.AddForce(float2(moveDir * accel, 0.0f)); // Accelerate if above minSpeed

	// Decelerate
	else rb.Friction(decel);
	//{
	//	if (xVel > 0)
	//	{
	//		rb.AddForce(float2(-decel, 0.0f));
	//		if (xVel < 0) rb.velocity.x = 0; // Stops overshoot
	//	}
	//	if (xVel < 0)
	//	{
	//		rb.AddForce(float2(decel, 0.0f));
	//		if (xVel > 0) rb.velocity.x = 0;
	//	}
	//}

	

	xVel = clamp(rb.velocity.x, -maxSpeed, maxSpeed);
}