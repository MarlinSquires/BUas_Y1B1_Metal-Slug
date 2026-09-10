#pragma once


class SpriteRenderer;

struct RenderLayer
{
	int count = 0;
	Renderer* layer[100];

	void Render();
};



class RenderSystem
{
public:

	void Render();

	// Sprites register and deregister themselves from renderLayers in their structors
	static void Register(int layer, Renderer* spr);
	static void Deregister(int layer, int index);

	RenderSystem();
	
	static RenderLayer* layers[5];

private:

	

};






