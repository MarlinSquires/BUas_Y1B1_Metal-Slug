#pragma once
#include "animationTypes.h"

// Holds animation-relevant structs and arrays



//------ Animation Clips --------------------------------------------------------------------------------------------------------------------------------------

struct ClipData
{
	AnimationClipName type; // Only used to verify that order between clipTable[] and AnimationClipType is consistent
	const char* address;
	int frameCount;
	int fps;
	bool looping;
	float2 offset;
};

inline constexpr float2 nullOffset = { 0.0f, 0.0f };
inline constexpr float2 playerUpperOffset = { 4.0f, -4.0f };
inline constexpr float2 playerLowerOffset = { 2.0f, 10.0f };


inline constexpr ClipData clipTable[] =
{
	{ AnimationClipName::Tileset, "assets/tileset.png", 4, 0, false, nullOffset },



	{ AnimationClipName::PlayerIdleUpper,	"assets/player/IdleUpper.png", 4, 12, true, playerUpperOffset },
	{ AnimationClipName::PlayerIdleLower,	"assets/player/IdleLower.png", 1, 12, true, playerLowerOffset },

	{ AnimationClipName::PlayerRunUpper,	"assets/player/RunUpper.png", 12, 12, true, playerUpperOffset  },
	{ AnimationClipName::PlayerRunLower,	"assets/player/RunLower.png", 12, 12, true, playerLowerOffset  },

	{ AnimationClipName::PlayerJumpUpper,	"assets/player/JumpUpper.png", 6, 12, true, playerUpperOffset  },
	{ AnimationClipName::PlayerJumpLower,	"assets/player/JumpLower.png", 6, 12, true, playerLowerOffset  },

	{ AnimationClipName::Enemy1Idle,		"assets/enemy/Enemy1Idle.png", 4, 12, true, nullOffset  },
	{ AnimationClipName::Enemy1Run,			"assets/enemy/Enemy1Run.png", 12, 12, true, nullOffset  },
	{ AnimationClipName::Enemy1Knife,		"assets/enemy/Enemy1Knife.png", 12, 12, true, nullOffset  },



	{ AnimationClipName::Ball, "assets/ball.png", 1, 0, false, nullOffset },

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
	AnimationClipName::Enemy1Knife,
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
};

