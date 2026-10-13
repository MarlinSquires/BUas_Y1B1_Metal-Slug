#include "precomp.h"
#include "renderers/textRenderer.h"
#include "central.h"




void TextRenderer::Render()
{
	if (text == nullptr) return;
	Central::surface->Print(text, (int)GetGameObject()->GetWorldPos().x, (int)GetGameObject()->GetWorldPos().y, colour);
}

