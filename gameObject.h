#pragma once

#include "precomp.h"
#include "component.h"

#include <vector>
#include <memory>


// Has a world-space position
// Can hold pointers to components like colliders and spriterenderers


class GameObject
{

public:

	// Position
	Tmpl8::float2 pos;

	bool debug = false; // Whether to draw origin, collider rect, etc


	virtual void Start(); // Init logic, runs after constructor
	virtual void Tick(); // Per-frame logic


	template <typename T, typename... Args>
	T& AddComponent(Args&&... args) {
		auto comp = make_unique<T>(forward<Args>(args)...);
		comp->gameObject = this;
		T& ref = *comp;
		components.push_back(move(comp));
		return ref;
	}

	template <typename T> T* GetComponent()
	{
		for (const auto& component : components) // Loops through components list by reference
		{
			T* ptr = dynamic_cast<T*>(component.get());
			if (ptr) return ptr;
		}
		return nullptr;
	}


	// Return tells you whether component was found and removed
	template<typename T> bool RemoveComponent()
	{
		for (auto& component : components)
		{
			T* ptr = dynamic_cast<T*>(component.get());
			if (ptr)
			{
				components.erase(component); // This is the issue here, im tryna erase by value instead of index
				return true;
			}
		}
		return false;
	}




	template<typename T> bool HasComponent()
	{
		for (const auto& component : components)
		{
			T* hasComponent = dynamic_cast<T*>(component.get());

			if (hasComponent) return true;
		}
		return false;
	}



	Component* GetComponents();

	void SetActive(bool isActive);


	// Constructors //
	GameObject(Tmpl8::float2 spawnPos) : pos(spawnPos) {};

	GameObject(Tmpl8::float2 spawnPos, bool debug) : pos(spawnPos), debug(debug) {};



private:

	Component* components[10];
	bool active = true; // Whether to run Tick() logic

	void DrawOrigin(); // To test whether origin is correctly at centre of sprite, instead of top-left



};

