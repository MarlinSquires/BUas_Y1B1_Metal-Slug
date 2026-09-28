#pragma once

#include "renderer.h"

enum class RenderLayerType;
enum class SpriteType;

// Sprites live in world-space
class SpriteRenderer : public Renderer
{
public:

	virtual void Start() override;

	void Render() override;


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
	void SetSprite(SpriteType spr);
	Sprite* GetSprite() { return sprite; }

	//Structors
	SpriteRenderer(RenderLayerType layer, Sprite* spr);
	SpriteRenderer(RenderLayerType layer, SpriteType spriteIndex, int frame = 0);

protected:

	Tmpl8::Sprite* sprite = nullptr;

private:

	int frameCount;
	int currentFrame = 0;



	Tmpl8::float2 size;

};

