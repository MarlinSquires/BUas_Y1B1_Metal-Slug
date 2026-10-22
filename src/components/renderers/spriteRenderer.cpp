#include "precomp.h"
#include "gameObject.h"

#include "renderers/spriteRenderer.h"
#include "renderSystem.h"
#include "central.h"
#include "animationLibrary.h"


// Sprites register and deregister themselves from renderLayers in their structors

#pragma region Structors

SpriteRenderer::SpriteRenderer(RenderLayerName layer) : Renderer(layer) 
{
	surface = Central::surface;
	camera = Central::camera;
};

SpriteRenderer::SpriteRenderer(RenderLayerName layer, Sprite* spr, float2 offset) : Renderer(layer), _offset(offset)
{
	SetSprite(spr);
	surface = Central::surface;
	camera = Central::camera;
};


SpriteRenderer::SpriteRenderer(RenderLayerName layer, AnimationClipName spr, float2 offset) : Renderer(layer), _offset(offset)
{
	SetSprite(spr);
	surface = Central::surface;
	camera = Central::camera;
	sprite->SetFrame(_currentFrame);
}


#pragma endregion


// Lifecycle
void SpriteRenderer::Start()
{
	if (camera == nullptr) camera = Central::camera; // In case of init issues
}

void SpriteRenderer::Tick()
{
	Renderer::Tick();
	CheckOffScreen();
}


void SpriteRenderer::Render()
{
	
	float2 originOffset = _size * 0.5; // Ensures origin is centre, not top-left

	int mult = _flipped ? -1 : 1;

	float2 screenPos = _gameObject->GetWorldPos() - originOffset - camOffset + (float2(_offset.x * mult, _offset.y));

	// Draw from centre rather than top left
	sprite->DrawFrame(surface,
		(int)round(screenPos.x),
		(int)round(screenPos.y),
		_currentFrame, _flipped
	);
}



// Setters
void SpriteRenderer::SetSprite(AnimationClipName spr)
{
	sprite = Central::animLib->GetClip(spr)->sprite;
	_offset = Central::animLib->GetClip(spr)->offset;
	_size.x = (float)sprite->GetWidth();
	_size.y = (float)sprite->GetHeight();
	_frameCount = sprite->Frames();
}

void SpriteRenderer::SetSprite(Sprite* spr)
{
	//if (spr == nullptr) printf("bla");
	sprite = spr;
	_size.x = (float)sprite->GetWidth();
	_size.y = (float)sprite->GetHeight();
	_frameCount = sprite->Frames();
}



// Logic
void SpriteRenderer::CheckOffScreen()
{
	float2 pos = _gameObject->GetWorldPos();
	float2 camPos = Central::camera->GetWorldPos();

	float xMin = camPos.x - SCRWIDTH / 2;
	float yMin = camPos.y - SCRHEIGHT / 2;

	float xMax = camPos.x + SCRWIDTH / 2;
	float yMax = camPos.y + SCRHEIGHT / 2;

	float width = (float)sprite->GetWidth();
	float height = (float)sprite->GetHeight();

	bool offX = (pos.x + width / 2 < xMin  || pos.x - width / 2 > xMax);
	bool offY = (pos.y + height / 2 < yMin || pos.y - height / 2 > yMax);
	
	if (offX || offY) _offScreen = true;
	else _offScreen = false;
}

