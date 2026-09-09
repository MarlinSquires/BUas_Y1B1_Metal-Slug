#pragma once



class CollisionSystem
{
public:

	void Register(int layer, Collider* col);
	void Deregister(int layer, int index);


private:
	CollisionLayer* layers[5];

};


class CollisionLayer
{

public:

	Collider* colliders[200] = {nullptr};
	int colCount;

};

