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

	// Getters
	int GetFrame() { return _currentFrame; }
	int GetFrameCount() { return _frameCount; }
	Sprite* GetSprite() { return sprite; }
	

	// Setters
	void SetSprite(AnimationClipName spr);
	void SetSprite(Sprite* spr);
	void SetOffset(float2 offset) { _offset = offset; }
	void SetFlipped(bool flipped) { _flipped = flipped; }
	

	//Structors
	SpriteRenderer(RenderLayerType layer);
	SpriteRenderer(RenderLayerType layer, Sprite* spr, float2 offset = { 0.0f, 0.0f });
	SpriteRenderer(RenderLayerType layer, AnimationClipName sprite, float2 offset = { 0.0f, 0.0f });

protected:

	Sprite* sprite = nullptr;

private:

	int _frameCount = 0;
	int _currentFrame = 0;
	bool _flipped = false;

	float2 _size;
	float2 _offset = { 0.0f, 0.0f };

};

