#include "precomp.h"
#include "spriteRenderer.h"
#include "central.h"
#include "animationClip.h"
#include "animationSet.h"
#include "animator.h"
#include "animationLibrary.h"
#include "renderSystem.h"


Animator::Animator(AnimationSetName set, int clip) : _set(Central::animLib->GetSet(set)), _clipIndex(clip)
{
	//_clip = _set->clips[clip];
}

void Animator::Start()
{
	_rend = &gameObject->AddComponent<SpriteRenderer>(RenderLayerType::Actors);

	SetClip(_clipIndex);
	//_rend->SetOffset(_clip->offset);
}

void Animator::SetClip(int index) 
{ 
	if (index > _set->clipCount) return;
	_clip = _set->clips[index]; 
	_rend->SetSprite(_clip->sprite);
	_rend->SetOffset(_clip->offset);

	_frameRate = _clip->fps;
	_timer = 1.0f / _frameRate;
};


void Animator::SetFlipped(bool flipped) 
{ 
	_flipped = flipped; 
	_rend->SetFlipped(_flipped);
}


void Animator::Tick()
{
	_timer -= Central::dts;

	if (_timer <= 0)
	{
		_rend->IncrementFrame();
		_timer = 1.0f / _frameRate;
	}
}


