#include "precomp.h"
#include "renderers/textRenderer.h"
#include "central.h"




void TextRenderer::Render()
{
	if (text == nullptr) return;
	Central::surface->Print(text, (int)_gameObject->GetWorldPos().x, (int)_gameObject->GetWorldPos().y, colour);
}

