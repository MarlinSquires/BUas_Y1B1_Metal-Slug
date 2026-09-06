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

	void Register(LayerType layer, SpriteRenderer* spr);
	void Deregister(LayerType layer, int index);

	RenderSystem();
	


private:

	void Render();

	RenderLayer* layers[5];

};




