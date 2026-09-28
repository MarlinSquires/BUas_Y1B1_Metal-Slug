#pragma once

// The Sprite() constructor takes 2 arguments: a file address, and a framecount. 
// I store each of those in a struct, which is then contained in an array
// This way I can simply pass an index to my BuildSprite() function and return a ptr to a new sprite

enum class SpriteType
{
	Tileset,
	Player,
	Ball
};

struct SpriteInfo
{
	const char* address;
	int frameCount;
};


class SpriteFactory
{

	static inline SpriteInfo sprites[] =
	{
		{ "assets/tileset.png", 4 },
		{ "assets/player_test.png", 1 },
		{ "assets/ball.png", 1 },
		
	};


public:
	
	static Sprite* BuildSprite(SpriteType sprite);

};








