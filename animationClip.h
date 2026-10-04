#pragma once

enum class AnimationClipName;

struct AnimationClip
{
	Sprite* sprite;
	int length;
	int fps;
	bool looping;

	AnimationClip(AnimationClipName clipType);
};

