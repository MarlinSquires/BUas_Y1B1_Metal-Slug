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

	enum LayerType
	{
		Background,
		BackgroundSprites,
		Actors,
		Projectiles,
		Foreground
	};

	static void Register(LayerType layer, SpriteRenderer* spr);
	static void Deregister(LayerType layer, int index);

	


private:

	void Render();

	static RenderLayer* layers[5];

	int layerCount;

};




