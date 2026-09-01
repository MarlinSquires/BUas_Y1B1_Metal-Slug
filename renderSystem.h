#pragma once


class SpriteRenderer;

class RenderSystem
{
public:

	void Register(int layer, SpriteRenderer* spr);
	void Deregister(int layer, SpriteRenderer* spr);

	enum Layer
	{
		Background,
		Actors,
		Projectiles,
		Foreground
	};


private:

	void Render();

	RenderLayer* layers[10];

	int layerCount;

};


class RenderLayer
{
public:
	int count;
	SpriteRenderer layer[100];

	void Insert(SpriteRenderer rend);

	void Iterate();

};

