#pragma once

enum class AnimationClipName;

struct AnimationClip
{
	Sprite* sprite;
	int length;
	int fps;
	bool looping;
	float2 offset;

	AnimationClip(AnimationClipName clipType);
};

