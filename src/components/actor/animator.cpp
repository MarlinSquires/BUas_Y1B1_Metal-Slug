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
	_rend = &_gameObject->AddComponent<SpriteRenderer>(_renderLayer);

	SetClip(_clipIndex);
}


void Animator::Tick()
{
	_timer -= Central::dts;

	if (_timer <= 0)
	{
		if (!_clip->looping && _rend->GetFrame() == _clip->length - 1)
		{
			_finished = true;
			return;
		}
		
		_rend->IncrementFrame();
		_timer = 1.0f / _frameRate;
	}
}



// Animator logic
void Animator::SetClip(int index) 
{ 
	assert(index <= _set->clipCount);
	_finished = false;

	_clip = _set->clips[index]; 
	_rend->SetSprite(_clip->sprite);
	_rend->SetOffset(_clip->offset);

	_rend->SetFrame(0);

	_frameRate = _clip->fps;
	_timer = 1.0f / _frameRate;
};

//void SetClip(AnimationClipName name)
//{
//
//	if (index > _set->clipCount) return;
//	_finished = false;
//
//	_clip = _set->clips[index];
//	_rend->SetSprite(_clip->sprite);
//	_rend->SetOffset(_clip->offset);
//
//	if (_rend->GetFrame() > _clip->length - 1) _rend->SetFrame(0);
//
//	_frameRate = _clip->fps;
//	_timer = 1.0f / _frameRate;
//
//
//}


void Animator::SetFlipped(bool flipped) 
{ 
	_flipped = flipped; 
	_rend->SetFlipped(_flipped);
}

void Animator::SetFrame(int frame) 
{ 
	_rend->SetFrame(frame); 
}


Sprite* Animator::GetSprite() const
{
	return _rend->GetSprite();
}

