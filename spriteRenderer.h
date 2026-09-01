#pragma once
#include "precomp.h"
#include "component.h"
#include "tmpl8math.h"


// Sprites live in world-space
class SpriteRenderer : public Component
{
public:

	// Specifically not override so it won't be called by gameObject->Tick()
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

	Tmpl8::Sprite* GetSprite() { return sprite.get(); };
	void SetSprite(std::string spriteName);

	//Structors
	SpriteRenderer(std::string spriteName);
	SpriteRenderer(std::string spriteName, int frame);

protected:

	int frameCount;
	int currentFrame = 0;

	Tmpl8::Surface* surface;
	GameObject* camera;
	std::unique_ptr<Tmpl8::Sprite> sprite;

	Tmpl8::float2 size;

	virtual void Draw(Tmpl8::float2 pos);

};

