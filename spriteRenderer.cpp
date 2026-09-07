#include "precomp.h"
#include "gameObject.h"

#include "spriteRenderer.h"
#include "renderSystem.h"
#include "central.h"


// Sprites register and deregister themselves from renderLayers in their structors

#pragma region Structors
SpriteRenderer::SpriteRenderer(int setLayer, Tmpl8::Sprite* spr) : sprite(spr)
{
	RenderSystem::Register(setLayer, this);
	layer = setLayer;
	index = RenderSystem::layers[setLayer]->count;
	
	size.x = (float)sprite->GetWidth();
	size.y = (float)sprite->GetHeight();
	surface = Central::surface;
	camera = Central::camera;

	frameCount = sprite->Frames();
}

SpriteRenderer::SpriteRenderer(int layer, int spr)
{
	RenderSystem::Register(layer, this);
	index = RenderSystem::layers[layer]->count;

	SetSprite(spr);
	size.x = (float)sprite->GetWidth();
	size.y = (float)sprite->GetHeight();
	surface = Central::surface;
	camera = Central::camera;

	frameCount = sprite->Frames();
};


SpriteRenderer::SpriteRenderer(int layer, int spr, int frame) : currentFrame(frame)
{
	RenderSystem::Register(layer, this);
	index = RenderSystem::layers[layer]->count;

	SetSprite(spr);
	size.x = (float)sprite->GetWidth();
	size.y = (float)sprite->GetHeight();
	surface = Central::surface;
	camera = Central::camera;

	frameCount = sprite->Frames();
	sprite->SetFrame(currentFrame);
}


SpriteRenderer::~SpriteRenderer()
{
	RenderSystem::Deregister(layer, index);
}

#pragma endregion

void SpriteRenderer::SetSprite(int spriteIndex)
{
	//sprite = move(SpriteFactory::BuildSprite(spriteName));
}


void SpriteRenderer::Draw(float2 pos)
{

	//if (camera == nullptr) camera = Central::camera; // In case of init issues

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

