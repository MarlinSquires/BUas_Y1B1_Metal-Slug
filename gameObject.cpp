#include "precomp.h"
#include "component.h"
#include "sceneManager.h"
#include "gameObject.h"



using namespace Tmpl8;

#pragma region Structors

GameObject::GameObject(Tmpl8::float2 spawnPos) : pos(spawnPos) 
{
	SceneManager::LoadObject(this);
	components = new Component*[10];
};


GameObject::GameObject(Tmpl8::float2 spawnPos, bool debug) : pos(spawnPos), debug(debug) 
{
	SceneManager::LoadObject(this);
	components = new Component*[10];
};

GameObject::GameObject(Tmpl8::float2 spawnPos, bool debug, int maxComponents) : pos(spawnPos), debug(debug)
{
	SceneManager::LoadObject(this);
	components = new Component*[maxComponents];
};

GameObject::~GameObject()
{
	delete[] components;
}

#pragma endregion




void GameObject::Start()
{
	for (int i = 0; i < compCount; i++)
	{
		components[i]->Start();
	}
}

void GameObject::Tick()
{
	if (!active) return;
	for (int i = 0; i < compCount; i++)
	{
		components[i]->Tick();
	}
	DrawOrigin();
}


void GameObject::SetActive(bool isActive)
{
	active = isActive;

	for (int i = 0; i < compCount; i++)
	{
		components[i]->active = active;
	}
}



void GameObject::DrawOrigin()
{
	if (!debug) return;

	//float2 offset = Central::camera->pos;
	//float2 screenPos = pos - offset;

	//Central::surface->Box(
	//	(int)round(screenPos.x - 2), // Rounding keeps box size consistent - truncation causes jitter
	//	(int)round(screenPos.y - 2),
	//	(int)round(screenPos.x + 2),
	//	(int)round(screenPos.y + 2),
	//	0xFF0000);
}

