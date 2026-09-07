#pragma once


class SpriteRenderer;

struct RenderLayer
{
	int count = 0;
	SpriteRenderer* layer[100];

	void Tick();
};



class RenderSystem
{
public:

	void Tick();

	// Sprites register and deregister themselves from renderLayers in their structors
	static void Register(int layer, SpriteRenderer* spr);
	static void Deregister(int layer, int index);

	RenderSystem();
	
	static RenderLayer* layers[5];

private:

	

};






