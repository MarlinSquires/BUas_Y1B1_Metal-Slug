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
};



inline constexpr ClipData clipTable[] =
{
	{ AnimationClipName::Tileset, "assets/tileset.png", 4, 0, false },



	{ AnimationClipName::PlayerIdleUpper,	"assets/player/IdleUpper.png", 4, 12, true },
	{ AnimationClipName::PlayerIdleLower,	"assets/player/IdleLower.png", 1, 12, true },

	{ AnimationClipName::PlayerRunUpper,	"assets/player/RunUpper.png", 12, 12, true  },
	{ AnimationClipName::PlayerRunLower,	"assets/player/RunLower.png", 12, 12, true  },

	{ AnimationClipName::PlayerFallUpper,	"assets/player/FallUpper.png", 6, 12, true  },
	{ AnimationClipName::PlayerFallLower,	"assets/player/FallLower.png", 6, 12, true  },

	{ AnimationClipName::Enemy1Idle,		"assets/enemy/Enemy1Idle.png", 4, 12, true  },
	{ AnimationClipName::Enemy1Run,			"assets/enemy/Enemy1Run.png", 12, 12, true  },
	{ AnimationClipName::Enemy1Knife,		"assets/enemy/Enemy1Knife.png", 12, 12, true  },



	{ AnimationClipName::Ball, "assets/ball.png", 1, 0, false },

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
	AnimationClipName::PlayerFallUpper, 
};

inline constexpr AnimationClipName playerLowerClips[] =
{
	AnimationClipName::PlayerIdleLower,
	AnimationClipName::PlayerRunLower,
	AnimationClipName::PlayerFallLower,
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

