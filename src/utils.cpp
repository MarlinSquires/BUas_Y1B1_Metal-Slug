#include "precomp.h"
#include "utils.h"


float utils::distance(float2 p1, float2 p2)
{
	float xDistance = p1.x - p2.x;
	float yDistance = p1.y - p2.y;

	return (float)sqrt((xDistance * xDistance) + (yDistance * yDistance)); // Finding hypotenuse
}


float random_range(float range)
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


bool flip()
{
	return (int)round(Rand(1)); // rounds to either 1 or 0
}


int rand_sign() // Randomly returns +1 or -1
{
	return utils::sign(
		Rand(1) - 0.5f); // Returns a number between -0.5 and 0.5
}








