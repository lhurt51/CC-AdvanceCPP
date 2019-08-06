#pragma once

#include "GameEngine/Core/ECS/Components.h"

namespace GameEngine
{
	class SceneManager
	{
	public:

		static void LoadScene(const std::string& path, const glm::vec2& pos);

	private:

		static void AddSceneCollision(const glm::vec2& pos);

	};
}

