#include "precomp.h"
#include "component.h"
#include "sceneManager.h"
#include "gameObject.h"



using namespace Tmpl8;

#pragma region Structors

GameObject::GameObject(float2 spawnPos, GameObject* parent, int maxComponents) : _parent(parent), _maxComponents(maxComponents)
{
	SceneManager::LoadObject(this);
	_components = new Component * [maxComponents]();
	_children = new GameObject * [10]();

	if (_parent != nullptr) SetParent(_parent);

	SetPos(spawnPos);
}


GameObject::~GameObject()
{
	// 2 step process is required to properly free up the memory of the components array
	for (int i = 0; i < _maxComponents; i++)
	{
		delete _components[i];
	}

	delete[] _components;

	SceneManager::UnloadObject(_index);
}

#pragma endregion




void GameObject::Start()
{
	for (int i = 0; i < _compCount; i++)
	{
		_components[i]->Start();
	}
}

void GameObject::Tick()
{
	if (!_active) return;
	for (int i = 0; i < _compCount; i++)
	{
		_components[i]->Tick();
	}
}


void GameObject::SetActive(bool isActive)
{
	_active = isActive;

	for (int i = 0; i < _compCount; i++)
	{
		_components[i]->active = _active;
	}
}


void GameObject::SetPos(float2 newPos)
{
	if (_parent == nullptr) _worldPos = newPos;
	else _worldPos = _parent->GetWorldPos() + _localPos;
	
	// Update positions of all children
	if (_childCount == 0) return;

	for (int i = 0; i < _childCount; i++)
	{
		_children[i]->SetPos(newPos);
	}
}



void GameObject::SetParent(GameObject* parent)
{
	_parent = parent;
	_parent->AddChild(this);
}

void GameObject::AddChild(GameObject* child)
{
	_children[_childCount++] = child;
}
