#pragma once

// The Sprite() constructor takes 2 arguments: a file address, and a framecount. 
// I store each of those in a struct, which is then contained in an array
// This way I can simply pass an index to my BuildSprite() function and return a ptr to a new sprite

enum class AnimationClipType;

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

		{ "assets/player/IdleUpper.png", 4 },
		{ "assets/player/IdleLower.png", 1 },

		{ "assets/player/RunUpper.png", 12 },
		{ "assets/player/RunLower.png", 12 },

		{ "assets/player/FallUpper.png", 6 },
		{ "assets/player/FallLower.png", 6 },


		{ "assets/ball.png", 1 },
		
	};


public:
	
	static Sprite* BuildSprite(AnimationClipType sprite);

};








