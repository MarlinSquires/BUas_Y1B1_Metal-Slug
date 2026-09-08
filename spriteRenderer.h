#pragma once

#include "component.h"


// Sprites live in world-space
class SpriteRenderer : public Component
{
public:


	virtual void Start() override;

	// Specifically not an override so it won't be called by gameObject->Tick()
	// Gets called by the renderSystem instead
	virtual void Tick();


	void SetFrame(int frame)
	{
		currentFrame = clamp(frame, 0, frameCount - 1);
		sprite->SetFrame(currentFrame);
	}

	void IncrementFrame(int amount)
	{
		int newFrame = currentFrame += amount;
		newFrame = clamp(newFrame, 0, frameCount);
	}

	int GetFrame() { return currentFrame; };

	int GetFrameCount() { return frameCount; };

	//Tmpl8::Sprite* GetSprite() { return sprite.get(); };
	void SetSprite(int spriteIndex);

	//Structors
	SpriteRenderer(int layer, Sprite* spr);
	SpriteRenderer(int layer, int spriteIndex);
	SpriteRenderer(int layer, int spriteIndex, int frame);
	~SpriteRenderer();

protected:

	int layer;
	int index; // index in layer. Used when removing self from layer array

	int frameCount;
	int currentFrame = 0;

	Tmpl8::Surface* surface;
	GameObject* camera;
	Tmpl8::Sprite* sprite = nullptr;

	Tmpl8::float2 size;

	virtual void Draw(Tmpl8::float2 pos);

};

