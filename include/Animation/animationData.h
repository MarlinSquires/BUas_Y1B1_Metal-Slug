#pragma once
#include "animationTypes.h"
#include "utils.h"

// Holds animation-relevant structs and arrays



//------ Animation Clips --------------------------------------------------------------------------------------------------------------------------------------

using should_loop = utils::bool_value<struct anim_loop_tag>;

struct ClipData
{
	AnimationClipName type; // Only used to verify that order between clipTable[] and AnimationClipType is consistent
	const char* address;
	int frameCount;
	int fps;
	should_loop looping;
	float2 offset;
};

inline constexpr float2 nullOffset = { 0.0f, 0.0f };
inline constexpr float2 playerUpperOffset = { 4.0f, -4.0f };
inline constexpr float2 playerLowerOffset = { 2.0f, 10.0f };


inline constexpr float2 enemy1KnifeOffset = { -6.0f, 0.0f };


inline constexpr ClipData clipTable[] =
{
	// Tiles
	{ AnimationClipName::Tileset,			"assets/tiles/tileset.png", 4, 0, should_loop::no, nullOffset },


	// Player
	{ AnimationClipName::PlayerIdleUpper,	"assets/player/idle_upper.png", 4, 6, should_loop::yes, playerUpperOffset },
	{ AnimationClipName::PlayerIdleLower,	"assets/player/idle_lower.png", 4, 6, should_loop::yes, playerLowerOffset },

	{ AnimationClipName::PlayerRunUpper,	"assets/player/run_upper.png", 12, 12, should_loop::yes, playerUpperOffset  },
	{ AnimationClipName::PlayerRunLower,	"assets/player/run_lower.png", 12, 12, should_loop::yes, playerLowerOffset  },

	{ AnimationClipName::PlayerJumpUpper,	"assets/player/jump_upper.png", 6, 12, should_loop::yes, playerUpperOffset  },
	{ AnimationClipName::PlayerJumpLower,	"assets/player/jump_lower.png", 6, 12, should_loop::yes, playerLowerOffset  },



	// Enemy1
	{ AnimationClipName::Enemy1Idle,		"assets/enemy/enemy_1_idle.png", 4, 12, should_loop::yes, nullOffset  },
	{ AnimationClipName::Enemy1Run,			"assets/enemy/enemy_1_run.png", 12, 12, should_loop::yes, nullOffset  },
	{ AnimationClipName::Enemy1Sneak,		"assets/enemy/enemy_1_sneak.png", 12, 12, should_loop::yes, nullOffset  },

	{ AnimationClipName::Enemy1Scared,		"assets/enemy/enemy_1_scared.png", 11, 12, should_loop::no, nullOffset  },
	{ AnimationClipName::Enemy1RunAway,		"assets/enemy/enemy_1_running_away.png", 12, 12, should_loop::yes, nullOffset  },

	{ AnimationClipName::Enemy1Knife,		"assets/enemy/enemy_1_knife.png", 12, 12, should_loop::no, enemy1KnifeOffset  },
	{ AnimationClipName::Enemy1Throwing,	"assets/enemy/enemy_1_throwing.png", 16, 12, should_loop::no, nullOffset },

	{ AnimationClipName::Enemy1Death,		"assets/enemy/enemy_1_death.png", 12, 12, should_loop::no, nullOffset  },
	


	// Projectiles
	{ AnimationClipName::Bullet,			"assets/weapons/pistol_bullet.png", 4, 0, should_loop::no, nullOffset },



	// Other
	{ AnimationClipName::Ball,				"assets/ball.png", 1, 0, should_loop::no, nullOffset },

};


constexpr bool ClipTableMatchesEnum()
{
	for (size_t i = 0; i < sizeof(clipTable) / sizeof(ClipData); ++i)
	{
		if (static_cast<size_t>(clipTable[i].type) != i) 
			return false;
		
		return true;
	}
}

// Asserts confirm that AnimationClipType and clipTable have the same entries in the same order
static_assert((sizeof(clipTable) / sizeof(ClipData)) == static_cast<size_t>(AnimationClipName::COUNT), "clipTable is missing entries!");

static_assert(ClipTableMatchesEnum(), "clipTable is out of order!");





//------ Animation Sets ---------------------------------------------------------------------------------------------------------------------------------------------------

inline constexpr AnimationClipName playerUpperClips[] =
{
	AnimationClipName::PlayerIdleUpper, 
	AnimationClipName::PlayerRunUpper,  
	AnimationClipName::PlayerJumpUpper, 
};

inline constexpr AnimationClipName playerLowerClips[] =
{
	AnimationClipName::PlayerIdleLower,
	AnimationClipName::PlayerRunLower,
	AnimationClipName::PlayerJumpLower,
};

inline constexpr AnimationClipName enemyClips[] =
{
	AnimationClipName::Enemy1Idle, 
	AnimationClipName::Enemy1Run,
	AnimationClipName::Enemy1Sneak,

	AnimationClipName::Enemy1Scared,
	AnimationClipName::Enemy1RunAway,

	AnimationClipName::Enemy1Knife,
	AnimationClipName::Enemy1Throwing,

	AnimationClipName::Enemy1Death,
};


inline constexpr AnimationClipName projectileClips[] =
{
	AnimationClipName::Bullet,
};

struct SetData
{
	const AnimationClipName* clips;
	int clipCount;
};


inline constexpr SetData animationSetTable[]
{
	{ playerUpperClips, (sizeof(playerUpperClips) / sizeof(AnimationClipName))},
	{ playerLowerClips, (sizeof(playerLowerClips) / sizeof(AnimationClipName))},

	{ enemyClips, (sizeof(enemyClips) / sizeof(AnimationClipName))},

	{ projectileClips, (sizeof(projectileClips) / sizeof(AnimationClipName))},
};

