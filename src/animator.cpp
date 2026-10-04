#include "precomp.h"
#include "spriteRenderer.h"
#include "central.h"
#include "animator.h"



void Animator::Start()
{
	_rend = gameObject->GetComponent<SpriteRenderer>();

	_timer = 1.0f / _frameRate;


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


