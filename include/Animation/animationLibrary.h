#pragma once

struct AnimationSet;
struct AnimationClip;

#include "animationTypes.h"
#include "animationClip.h"
#include "animationSet.h"


// Instantiates all animation sets, clips, and sprites upon program startup, and hands out pointers when requested
// The Sprite::DrawFrame() function means that multiple objects can share the same sprite without issue

class AnimationLibrary
{
public:

	void Init();
	AnimationSet* GetSet(AnimationSetName name) { return sets[static_cast<int>(name)]; }
	AnimationClip* GetClip(AnimationClipName name) { return clips[static_cast<int>(name)]; }

private:
	
	AnimationSet* sets[static_cast<int>(AnimationSetName::COUNT)];
	AnimationClip* clips[static_cast<int>(AnimationClipName::COUNT)];


};

