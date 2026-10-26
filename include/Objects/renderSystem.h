#pragma once


class Renderer;



enum class RenderLayerName : uint8_t
{
	Background,
	BGSprites,
	BGActors,
	MGActors,
	FGActors,
	FGSprites,
	Text,
	Debug,
	COUNT
};


struct RenderLayer
{
	int count = 0;
	Renderer* renderers[1024];

	void Render();
};



class RenderSystem
{
public:

	void Render();

	// Sprites register and deregister themselves from renderLayers in their structors
	static void Register(RenderLayerName layer, Renderer* renderer);
	static void Deregister(RenderLayerName layer, const int index);
	static RenderLayer& GetLayer(RenderLayerName layer);

private:

	static inline RenderLayer layers[static_cast<int>(RenderLayerName::COUNT)];

};






