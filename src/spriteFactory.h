#pragma once

// The Sprite() constructor takes 2 arguments: a file address, and a framecount. 
// I store each of those in a struct, which is then contained in an array
// This way I can simply pass an index to my BuildSprite() function and return a ptr to a new sprite


struct SpriteInfo
{
	const char* address;
	int frameCount;
};


class SpriteFactory
{

	static inline SpriteInfo sprites[] =
	{
		{ "assets/ball.png", 1 },
		{ "assets/aagun.tga", 36 }
	};


public:
	
	static Sprite* BuildSprite(int sprite);

};








