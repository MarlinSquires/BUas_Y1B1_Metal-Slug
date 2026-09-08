#pragma once

// The Sprite() constructor takes 2 arguments: a file address, and a framecount. 
// I store each of those in separate arrays (but the same index for each sprite)
// This way I can simply pass an index to my BuildSprite() function and return a ptr to a new sprite


class SpriteFactory
{

	static inline const char* addresses[] = 
	{
		"assets/ball.png",
		"assets/aagun.tga"
	};

	static inline int frameCounts[] =
	{
		1,
		36,
	};

public:
	
	static void Init();
	static Sprite* BuildSprite(int sprite);

};




