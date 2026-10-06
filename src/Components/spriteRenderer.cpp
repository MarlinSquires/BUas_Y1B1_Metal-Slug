#include "precomp.h"
#include "gameObject.h"

#include "spriteRenderer.h"
#include "renderSystem.h"
#include "central.h"
#include "animationLibrary.h"


// Sprites register and deregister themselves from renderLayers in their structors

#pragma region Structors

SpriteRenderer::SpriteRenderer(RenderLayerType layer) : Renderer(layer) 
{
	surface = Central::surface;
	camera = Central::camera;
};

SpriteRenderer::SpriteRenderer(RenderLayerType layer, Sprite* spr, float2 offset) : Renderer(layer), _offset(offset)
{
	SetSprite(spr);
	surface = Central::surface;
	camera = Central::camera;
};


SpriteRenderer::SpriteRenderer(RenderLayerType layer, AnimationClipName spr, float2 offset) : Renderer(layer), _offset(offset)
{
	SetSprite(spr);
	surface = Central::surface;
	camera = Central::camera;
	sprite->SetFrame(_currentFrame);
}


#pragma endregion



void SpriteRenderer::SetSprite(AnimationClipName spr)
{
	sprite = Central::animLib->GetClip(spr)->sprite;
	//_offset = Central::animLib->GetClip(spr)->offset;
	_size.x = (float)sprite->GetWidth();
	_size.y = (float)sprite->GetHeight();
	_frameCount = sprite->Frames();
}

void SpriteRenderer::SetSprite(Sprite* spr)
{
	sprite = spr;
	_size.x = (float)sprite->GetWidth();
	_size.y = (float)sprite->GetHeight();
	_frameCount = sprite->Frames();
}


void SpriteRenderer::Start()
{
	if (camera == nullptr) camera = Central::camera; // In case of init issues
}


void SpriteRenderer::Render()
{
	float2 camOffset = Central::camera->GetWorldPos();
	float2 originOffset = _size * 0.5; // Ensures origin is centre, not top-left

	int mult = _flipped ? -1 : 1;

	float2 screenPos = gameObject->GetWorldPos() - originOffset - camOffset + (float2(_offset.x * mult, _offset.y));

	// Draw from centre rather than top left
	sprite->DrawFrame(surface,
		(int)round(screenPos.x),
		(int)round(screenPos.y),
		_currentFrame, _flipped
	);
}

