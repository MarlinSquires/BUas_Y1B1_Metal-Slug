#include "precomp.h"
#include "component.h"
#include "spriteRenderer.h"
#include "gameObject.h"
#include "central.h"


SpriteRenderer::SpriteRenderer(int spriteIndex)
{
	SetSprite(spriteIndex);
	size.x = (float)sprite->GetWidth();
	size.y = (float)sprite->GetHeight();
	surface = Central::surface;
	camera = Central::camera;

	frameCount = sprite->Frames();
};


SpriteRenderer::SpriteRenderer(int spriteIndex, int frame) : currentFrame(frame)
{
	SetSprite(spriteIndex);
	size.x = (float)sprite->GetWidth();
	size.y = (float)sprite->GetHeight();
	surface = Central::surface;
	camera = Central::camera;

	frameCount = sprite->Frames();
	sprite->SetFrame(currentFrame);
}


void SpriteRenderer::SetSprite(int spriteIndex)
{
	//sprite = move(SpriteFactory::BuildSprite(spriteName));
}


void SpriteRenderer::Draw(float2 pos)
{

	if (camera == nullptr) camera = Central::camera; // In case of init issues

	float2 camOffset = Central::camera->pos;
	float2 originOffset = size * 0.5; // Ensures origin is centre, not top-left

	float2 screenPos = pos - originOffset - camOffset;

	// Only draw if within viewport


	// Draw from centre rather than top left
	sprite->Draw(surface,
		(int)round(screenPos.x),
		(int)round(screenPos.y)
	);

}

void SpriteRenderer::Tick()
{
	Draw(gameObject->pos);
}

