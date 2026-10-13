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
	void MarkForDestruction();

	void JumpStartComponent(Component* comp); // Runs Start() and PostStart() component, if its added to GO after scene initialization

	// Components
	template <typename T, typename... Args>
	T& AddComponent(Args&&... args)
	{
		T* comp = new T(forward<Args>(args)...);
		comp->_gameObject = this;
		T& ref = *comp;
		_components[_compCount++] = comp;
		JumpStartComponent(comp);
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

	// Getters
	float2 GetWorldPos() const { return _worldPos; }
	float2 GetLocalPos() const { return _localPos; }
	const GameObject* GetParent() const { return _parent; }
	int GetChildCount() const { return _childCount; }
	bool PendingDestruction() const { return _pendingDestroy; }


	// Setters
	void SetPos(float2 newPos); // set pos to this value
	void UpdatePos(float2 moveBy); // increment pos by this value
	void SetParent(GameObject* parent);
	void SetActive(bool isActive);
	

	// Other
	void AddChild(GameObject* child);
	bool debug = false; // Whether to draw origin, collider rect, etc
	int index = 0; // used in destructor to remove self from scene gameObjects[] array


	// Structors //
	GameObject(float2 spawnPos = {0.0f, 0.0f}, GameObject* parent = nullptr, int maxComponents = 20);
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
	int _maxComponents = 20;
	Component** _components; // Max components per GO

	// Other
	int _maxChildren = 10;
	
	bool _active = true; // Whether to run Tick() logic
	bool _pendingDestroy = false;

	
};

