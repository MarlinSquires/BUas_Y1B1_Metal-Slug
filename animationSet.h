#pragma once

enum class AnimationSetName;
struct AnimationClip;
class AnimationLibrary;

// Holds a number of animation clips (sprites) for a single object (e.g all player anims)
// The animationController switches between these as necessary

struct AnimationSet
{
	AnimationClip** clips;
	int clipCount;
	AnimationSet(AnimationLibrary* lib, AnimationSetName setType);
};

