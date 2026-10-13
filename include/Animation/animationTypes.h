#pragma once


// Holds animation-relevant enums

enum class AnimationSetName : uint8_t
{
	PlayerUpper,
	PlayerLower,

	Enemy,

	Projectiles,

	COUNT // Used to verify number of elements in enum
};



enum class AnimationClipName : uint8_t
{
	Tileset,


	PlayerIdleUpper,
	PlayerIdleLower,

	PlayerRunUpper,
	PlayerRunLower,

	PlayerJumpUpper,
	PlayerJumpLower,

	Enemy1Idle,
	Enemy1Run,
	Enemy1Knife,

	Bullet,




	Ball,

	COUNT, // Used to verify number of elements in enum
};

