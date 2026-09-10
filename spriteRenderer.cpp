#include "precomp.h"
#include "gameObject.h"

#include "spriteRenderer.h"
#include "renderSystem.h"
#include "central.h"
#include "spriteFactory.h"


// Sprites register and deregister themselves from renderLayers in their structors

#pragma region Structors


SpriteRenderer::SpriteRenderer(int layer, Sprite* spr) : Renderer(layer)
{
	
	sprite = spr;
	size.x = (float)sprite->GetWidth();
	size.y = (float)sprite->GetHeight();
	surface = Central::surface;
	camera = Central::camera;

	frameCount = sprite->Frames();
};

SpriteRenderer::SpriteRenderer(int layer, int spr) : Renderer(layer)
{

	SetSprite(spr);
	size.x = (float)sprite->GetWidth();
	size.y = (float)sprite->GetHeight();
	surface = Central::surface;
	camera = Central::camera;

	frameCount = sprite->Frames();
};


SpriteRenderer::SpriteRenderer(int layer, int spr, int frame) : Renderer(layer), currentFrame(frame)
{
	SetSprite(spr);
	size.x = (float)sprite->GetWidth();
	size.y = (float)sprite->GetHeight();
	surface = Central::surface;
	camera = Central::camera;

	frameCount = sprite->Frames();
	sprite->SetFrame(currentFrame);
}


#pragma endregion

void SpriteRenderer::SetSprite(int spriteIndex)
{
	if (sprite != nullptr) delete sprite;
	sprite = SpriteFactory::BuildSprite(spriteIndex);
}

void SpriteRenderer::Start()
{
	if (camera == nullptr) camera = Central::camera; // In case of init issues
}


void SpriteRenderer::Render()
{
	float2 camOffset = Central::camera->pos;
	float2 originOffset = size * 0.5; // Ensures origin is centre, not top-left

	float2 screenPos = gameObject->pos - originOffset - camOffset;

	// Only draw if within viewport


	// Draw from centre rather than top left
	sprite->Draw(surface,
		(int)round(screenPos.x),
		(int)round(screenPos.y)
	);
}

