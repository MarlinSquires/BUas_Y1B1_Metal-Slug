#include "precomp.h"

#include "animationClip.h"
#include "animationSet.h"
//#include "animationTypes.h"
#include "animationData.h"
#include "animationLibrary.h"


// Init all clips directly, then init sets using the indices in the sets[] array

void AnimationLibrary::Init()
{
	// Instantiate all clips
	for (int i = 0; i < static_cast<int>(AnimationClipName::COUNT); i++)
	{
		clips[i] = new AnimationClip(static_cast<AnimationClipName>(i));
	}

	// Instantiate all sets
	for (int i = 0; i < static_cast<int>(AnimationSetName::COUNT); i++)
	{
		sets[i] = new AnimationSet(this, static_cast<AnimationSetName>(i));
	}
}