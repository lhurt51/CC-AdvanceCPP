#pragma once

#include <vector>
#include <glm/glm.hpp>

namespace GameEngine
{
	class SceneManager
	{
	public:

		static void LoadScene(const std::string& path, const glm::vec2& pos);
		static bool IsPositionValid(const glm::vec2& pos);

	private:

		static void AddSceneCollision(const glm::vec2& pos);
		static void NewPosAIPath(const glm::vec2& pos);

	private:

		static std::vector<glm::vec2> m_AIPath;

	};
}

