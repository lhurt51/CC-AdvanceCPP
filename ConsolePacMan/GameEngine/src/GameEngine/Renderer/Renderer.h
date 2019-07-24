#pragma once

#include "RenderCommand.h"

namespace GameEngine
{
	class Renderer
	{
	public:

		static void BeginScene(); // Todo: take in scene parameters (Camera)
		static void EndScene();

		static void Submit(const SpriteInfo& sprite);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:

		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* s_SceneData;

	};
}

