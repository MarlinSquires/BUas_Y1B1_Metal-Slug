#pragma once

#include "renderer.h"

enum class RenderLayerName : uint8_t;
enum class AnimationClipName : uint8_t;
class AnimationLibrary;

// Sprites live in world-space
class SpriteRenderer : public Renderer
{
public:

	// Lifecycle
	void Start() override;
	void Tick() override;

	void Render() override;


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
	bool OffScreen() { return _offScreen; }

	// Setters
	void SetSprite(AnimationClipName spr);
	void SetSprite(Sprite* spr);
	void SetOffset(float2 offset) { _offset = offset; }
	void SetFlipped(bool flipped) { _flipped = flipped; }
	void SetFrame(int frame)
	{
		_currentFrame = clamp(frame, 0, _frameCount - 1);
		//sprite->SetFrame(_currentFrame);
	}
	

	//Structors
	SpriteRenderer(RenderLayerName layer);
	SpriteRenderer(RenderLayerName layer, Sprite* spr, float2 offset = { 0.0f, 0.0f });
	SpriteRenderer(RenderLayerName layer, AnimationClipName sprite, float2 offset = { 0.0f, 0.0f });

protected:

	void CheckOffScreen();

	Sprite* sprite = nullptr;

private:

	int _frameCount = 0;
	int _currentFrame = 0;
	bool _flipped = false;
	bool _offScreen = true;

	float2 _size;
	float2 _offset = { 0.0f, 0.0f };

};

