#include "precomp.h"
#include "animationLibrary.h"
#include "animationData.h"
#include "animationSet.h"



AnimationSet::AnimationSet(AnimationLibrary* lib, AnimationSetName setType)
{
	const SetData& data = animationSetTable[static_cast<int>(setType)];
	clipCount = data.clipCount;
	clips = new AnimationClip * [clipCount];

	for (int i = 0; i < clipCount; i++)
	{
		clips[i] = lib->GetClip(data.clips[i]);
	}
}



