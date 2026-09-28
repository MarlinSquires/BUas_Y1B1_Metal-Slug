#include "precomp.h"
#include "textRenderer.h"
#include "central.h"




void TextRenderer::Render()
{
	if (text == nullptr) return;
	Central::surface->Print(text, gameObject->pos.x, gameObject->pos.y, colour);
}

