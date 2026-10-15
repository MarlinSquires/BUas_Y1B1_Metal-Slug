#include "precomp.h"
#include "utils.h"


float utils::distance(float2 p1, float2 p2)
{
	float xDistance = p1.x - p2.x;
	float yDistance = p1.y - p2.y;

	return (float)sqrt((xDistance * xDistance) + (yDistance * yDistance)); // Finding hypotenuse
}


float utils::random_range(float range)
{
	// Bit of a hacky way to get a random range but i think it works?
	float r = Rand(2 * range);

	if (r > range)
	{
		r -= range;
		r = -r;
	}
	return r;
}

float utils::random_range(float min, float max)
{
	return Rand(max - min) + min;
}


bool utils::flip()
{
	return (bool)round(RandomFloat()); // rounds to either 1 or 0
}


int utils::rand_sign() // Randomly returns +1 or -1
{
	return utils::sign(
		Rand(1) - 0.5f); // Returns a number between -0.5 and 0.5
}


int utils::dir_to_frame(float2 dir)
{
	const float T = 0.41421356f; // tan(22.5 degrees)

	// Opposite directions share a frame, so fold into the upper half
	if (dir.y < 0.0f)
	{
		dir.x = -dir.x;
		dir.y = -dir.y;
	}

	float ax = dir.x < 0.0f ? -dir.x : dir.x;

	if (ax <= dir.y * T) return 0; // mostly vertical
	if (dir.y <= ax * T) return 2; // mostly horizontal
	return dir.x > 0.0f ? 3 : 1;   // diagonal: up-right / up-left
}








