#include "precomp.h"
#include "animationLibrary.h"
#include "animationData.h"
#include "animationClip.h"



AnimationClip::AnimationClip(AnimationClipName type)
{
	const ClipData& data = clipTable[static_cast<int>(type)];
	sprite = new Sprite(new Surface(data.address), data.frameCount);
	fps = data.fps;
	length = sprite->Frames();
	looping = data.looping;
	offset = data.offset;
};
