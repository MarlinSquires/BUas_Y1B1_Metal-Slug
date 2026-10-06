#pragma once


class Renderer;



enum class RenderLayerType
{
	Background,
	BackgroundSprites,
	Actors,
	ForegroundSprites,
	Text,
	Debug
};


struct RenderLayer
{
	int count = 0;
	Renderer* renderers[100];

	void Render();
};



class RenderSystem
{
public:

	void Render();

	// Sprites register and deregister themselves from renderLayers in their structors
	static void Register(RenderLayerType layer, Renderer* spr);
	static void Deregister(RenderLayerType layer, int index);
	static RenderLayer& GetLayer(RenderLayerType layer);
	

private:

	static inline RenderLayer layers[] =
	{
		RenderLayer(),
		RenderLayer(),
		RenderLayer(),
		RenderLayer(),
		RenderLayer(),
		RenderLayer()
	};

};






