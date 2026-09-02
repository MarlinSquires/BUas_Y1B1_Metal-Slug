#pragma once
#include "precomp.h"

class Component;

// Sprites live in world-space
class SpriteRenderer : public Component
{
public:

	// Specifically not an override so it won't be called by gameObject->Tick()
	// Gets called by the renderSystem instead
	virtual void Tick();

	void SetIndex(int i)
	{
		index = i;
	}


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

	Tmpl8::Sprite* GetSprite() { return sprite.get(); };
	void SetSprite(int spriteIndex);

	//Structors
	SpriteRenderer(int spriteIndex);
	SpriteRenderer(int spriteIndex, int frame);

protected:

	int index; // index in layer. Used when removing self from layer array

	int frameCount;
	int currentFrame = 0;

	Tmpl8::Surface* surface;
	GameObject* camera;
	Tmpl8::Sprite* sprite;

	Tmpl8::float2 size;

	virtual void Draw(Tmpl8::float2 pos);

};

