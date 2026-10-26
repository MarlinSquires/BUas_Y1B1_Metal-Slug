#include "precomp.h"
#include "renderers/textRenderer.h"
#include "central.h"




void TextRenderer::Render()
{
	if (_text == nullptr) return;
	Central::surface->Print(_text, (int)_gameObject->GetWorldPos().x, (int)_gameObject->GetWorldPos().y, _colour);
}

