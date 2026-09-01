#pragma once

#include "spriteRenderer.h"


// Images live in screen-space
class Image : public SpriteRenderer
{
public:

	void Tick() override;


	// Structors
	//Image(std::string spriteName) : SpriteRenderer::SpriteRenderer(std::string spriteName);

private:

	void Draw(Tmpl8::float2 pos) override;


};

