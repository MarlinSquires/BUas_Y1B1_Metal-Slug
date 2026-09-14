#include "precomp.h"
#include "surface.h"
#include "spriteFactory.h"



// Returns a ptr to a newly constructed sprite
// Takes the indices of the 2 data arrays as an argument
Sprite* SpriteFactory::BuildSprite(int spr)
{
	return new Sprite(new Surface(sprites[spr].address), sprites[spr].frameCount);
}
