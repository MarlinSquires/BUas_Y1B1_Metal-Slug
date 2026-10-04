#include "precomp.h"
#include "gameObject.h"

#include "spriteRenderer.h"
#include "renderSystem.h"
#include "central.h"
#include "animationLibrary.h"


// Sprites register and deregister themselves from renderLayers in their structors

#pragma region Structors


SpriteRenderer::SpriteRenderer(RenderLayerType layer, Sprite* spr, float2 offset) : Renderer(layer), _offset(offset)
{
	sprite = spr;
	_size.x = (float)sprite->GetWidth();
	_size.y = (float)sprite->GetHeight();
	surface = Central::surface;
	camera = Central::camera;

	_frameCount = sprite->Frames();
};



SpriteRenderer::SpriteRenderer(RenderLayerType layer, AnimationClipName spr, float2 offset) : Renderer(layer), _offset(offset)
{
	SetSprite(spr);
	_size.x = (float)sprite->GetWidth();
	_size.y = (float)sprite->GetHeight();
	surface = Central::surface;
	camera = Central::camera;

	_frameCount = sprite->Frames();
	sprite->SetFrame(_currentFrame);
}


#pragma endregion

void SpriteRenderer::SetSprite(AnimationClipName spr)
{
	sprite = Central::animLib->GetClip(spr)->sprite;
}

void SpriteRenderer::Start()
{
	if (camera == nullptr) camera = Central::camera; // In case of init issues
}


void SpriteRenderer::Render()
{
	float2 camOffset = Central::camera->GetWorldPos();
	float2 originOffset = _size * 0.5; // Ensures origin is centre, not top-left

	float2 screenPos = gameObject->GetWorldPos() - originOffset - camOffset + _offset;

	// Only draw if within viewport

	// Draw from centre rather than top left
	sprite->Draw(surface,
		(int)round(screenPos.x),
		(int)round(screenPos.y)
	);
}

