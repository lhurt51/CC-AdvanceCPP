#include "gepch.h"
#include "Renderer.h"

namespace GameEngine
{

	Renderer::SceneData* Renderer::s_SceneData = new SceneData;

	void Renderer::Renderer::BeginScene()
	{
		// Set maybe view projection matrix
	}

	void Renderer::EndScene()
	{
		// RenderCommand::Flush
	}

	void Renderer::Submit(const SpriteInfo& sprite)
	{
		RenderCommand::DrawSprite({ 0, 0 }, sprite);
	}

}