#pragma once



class RenderLayer
{
public:
	int count = 0;
	SpriteRenderer* layer[100];

	void Iterate();

};


class RenderSystem
{
public:

	enum Layer
	{
		Background,
		BackgroundSprites,
		Actors,
		Projectiles,
		Foreground
	};

	static void Register(Layer layer, SpriteRenderer* spr);
	static void Deregister(Layer layer, int index);

	


private:

	void Render();

	static RenderLayer* layers[5];

	int layerCount;

};




