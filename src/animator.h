#pragma once
#include "component.h"

class SpriteRenderer;
struct AnimationClip;

class Animator : public Component
{

public:

	void Start() override;
	void Tick() override;


	void Play(int targetClip, bool waitTillEnd, AnimationClipName nextClip);

	void PlayAnim() { _animating = true; };
	void PauseAnim() { _animating = false; };


private:


	bool _animating = true;
	int _frameRate = 12;
	int _currentFrame = 0; // Since sprites are shared, the animator needs to track the current frame
	float _timer = 0;

	AnimationClip* _clip;
	SpriteRenderer* _rend;




};

