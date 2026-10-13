#include "precomp.h"
#include "spriteRenderer.h"
#include "central.h"
#include "animationClip.h"
#include "animationSet.h"
#include "animator.h"
#include "animationLibrary.h"
#include "renderSystem.h"


Animator::Animator(RenderLayerName renderLayer, AnimationSetName set, int clip) : 
	_renderLayer(renderLayer), _set(Central::animLib->GetSet(set)), _clipIndex(clip) {}

// Lifecycle

void Animator::Start()
{
	_rend = &GetGameObject()->AddComponent<SpriteRenderer>(_renderLayer);

	SetClip(_clipIndex);
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



// Animator logic
void Animator::SetClip(int index) 
{ 
	if (index > _set->clipCount) return;
	_clip = _set->clips[index]; 
	_rend->SetSprite(_clip->sprite);
	_rend->SetOffset(_clip->offset);
	if (_rend->GetFrame() > _clip->length - 1) _rend->SetFrame(0);

	_frameRate = _clip->fps;
	_timer = 1.0f / _frameRate;
};


void Animator::SetFlipped(bool flipped) 
{ 
	_flipped = flipped; 
	_rend->SetFlipped(_flipped);
}


Sprite* Animator::GetSprite() const
{
	return _rend->GetSprite();
}

