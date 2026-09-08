#include "precomp.h"
#include "surface.h"
#include "spriteFactory.h"



// Initialize arrays that hold sprite data
void SpriteFactory::Init()
{
	addresses[0] = "assets/ball.png";
	frameCounts[0] = 1;

	addresses[1] = "assets/aagun.tga";
	frameCounts[1] = 36;
}

// Returns a ptr to a newly constructed sprite
// Takes the indices of the 2 data arrays as an argument
Sprite* SpriteFactory::BuildSprite(int sprite)
{
	return new Sprite(new Surface(addresses[sprite]), frameCounts[sprite]);
}
