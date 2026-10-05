#pragma once


class Component;
class Transform;


// Can hold pointers to components like colliders and spriterenderers


class GameObject
{

public:

	// Lifecycle
	virtual void Start(); // Init logic, runs after constructor
	virtual void PostStart(); // Runs after Start()
	virtual void Tick(); // Per-frame logic


	// Components
	template <typename T, typename... Args>
	T& AddComponent(Args&&... args)
	{
		T* comp = new T(forward<Args>(args)...);
		comp->gameObject = this;
		T& ref = *comp;
		_components[_compCount++] = comp;
		return ref;
	};


	template <typename T> T* GetComponent()
	{
		for (int i = 0; i < _compCount; i++) // Loops through components list by reference
		{
			T* ptr = dynamic_cast<T*>(_components[i]);
			if (ptr) return ptr;
		}
		return nullptr;
	}

	// Positioning
	void SetPos(float2 newPos);
	float2 GetWorldPos() { return _worldPos; }
	float2 GetLocalPos() { return _localPos; }


	// Parenting
	GameObject* GetParent() { return _parent; }
	int GetChildCount() { return _childCount; }
	void SetParent(GameObject* parent);
	void AddChild(GameObject* child);

	// Other
	void SetActive(bool isActive);
	void SetIndex(int i) { _index = i; }
	bool debug = false; // Whether to draw origin, collider rect, etc


	// Structors //
	GameObject(float2 spawnPos = {0.0f, 0.0f}, GameObject* parent = nullptr, int maxComponents = 10);
	~GameObject();

	
private:

	// Parenting
	GameObject* _parent = nullptr;
	GameObject** _children;
	int _childCount = 0;

	// Position
	float2 _localPos = { 0.0f, 0.0f };
	float2 _worldPos = { 0.0f, 0.0f };

	// Components
	int _compCount = 0;
	int _maxComponents = 10;
	Component** _components; // Max 10 components per GO

	// Other
	int _index = 0; // used in destructor to remove self from scene gameObjects[] array
	bool _active = true; // Whether to run Tick() logic

	
};

