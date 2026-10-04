#pragma once

#include "renderer.h"

enum class RenderLayerType;
enum class AnimationClipName;
class AnimationLibrary;

// Sprites live in world-space
class SpriteRenderer : public Renderer
{
public:

	virtual void Start() override;

	void Render() override;


	void SetFrame(int frame)
	{
		_currentFrame = clamp(frame, 0, _frameCount - 1);
		sprite->SetFrame(_currentFrame);
	}

	void IncrementFrame()
	{
		_currentFrame++;
		if (_currentFrame >= _frameCount) _currentFrame = 0;
		sprite->SetFrame(_currentFrame);
	}

	int GetFrame() { return _currentFrame; };

	int GetFrameCount() { return _frameCount; };

	void SetSprite(AnimationClipName spr);
	Sprite* GetSprite() { return sprite; }

	//Structors
	SpriteRenderer(RenderLayerType layer, Sprite* spr, float2 offset = { 0.0f, 0.0f });
	SpriteRenderer(RenderLayerType layer, AnimationClipName spriteIndex, float2 offset = { 0.0f, 0.0f });

protected:

	Sprite* sprite = nullptr;

private:

	int _frameCount;
	int _currentFrame = 0;

	AnimationLibrary* _lib;

	float2 _size;
	float2 _offset = { 0.0f, 0.0f };

};

