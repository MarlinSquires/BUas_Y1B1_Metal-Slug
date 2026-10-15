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

	// Player
	PlayerIdleUpper,
	PlayerIdleLower,

	PlayerRunUpper,
	PlayerRunLower,

	PlayerJumpUpper,
	PlayerJumpLower,



	// Enemy1
	Enemy1Idle,
	Enemy1Run,
	Enemy1Sneak,

	Enemy1Scared,
	Enemy1RunAway,

	Enemy1Knife,
	Enemy1Throwing,

	Enemy1Death,



	Bullet,




	Ball,

	COUNT, // Used to verify number of elements in enum
};

