#pragma once
#include "component.h"

class SpriteRenderer;
struct AnimationClip;
struct AnimationSet;

enum class AnimationClipName : uint8_t;
enum class AnimationSetName : uint8_t;
enum class RenderLayerName : uint8_t;

// Drives a SpriteRenderer, settings its sprite and handling frame incrementation
// Uses AddComponent() to instantiate a SpriteRenderer component, non-owning

class Animator : public Component
{
public:

	void Start() override;
	void Tick() override;

	// Getters
	Sprite* GetSprite() const;

	// Setters
	void SetClip(int index);
	void SetFlipped(bool flipped);

	// Structors
	Animator(RenderLayerName renderLayer, AnimationSetName set, int clip = 0);


private:

	bool _animating = true;
	bool _flipped = false;
	int _frameRate = 12; // Caches framerate from currently held clip
	float _timer = 0;

	int _clipIndex = 0;

	AnimationSet* _set = nullptr;
	AnimationClip* _clip = nullptr;
	SpriteRenderer* _rend = nullptr;
	RenderLayerName _renderLayer;




};

