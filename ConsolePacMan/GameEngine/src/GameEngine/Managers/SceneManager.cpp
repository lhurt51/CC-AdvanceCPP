#include "gepch.h"
#include "SceneManager.h"

#include "GameEngine/Application.h"
#include "GameEngine/Managers/AssetManager.h"

namespace GameEngine
{

	std::vector<glm::vec2> SceneManager::m_AIPath;

	void SceneManager::LoadScene(const std::string& path, const glm::vec2& pos)
	{
		SpriteInfo& map = Application::Get().m_Assets->GetSprite(path);
		for (int y = 0; y < map.size.y; y++)
		{
			for (int x = 0; x < map.size.x; x++)
			{
				glm::vec2 tmp = { pos.x + x, pos.y + y };
				if (map.GetGlyph(x, y) != L'.' && map.GetGlyph(x, y) != L'o')
					AddSceneCollision(tmp);
				else if (map.GetGlyph(x, y) == L'.' || map.GetGlyph(x, y) == L'o')
					NewPosAIPath(tmp);
			}
		}
	}

	bool SceneManager::IsPositionValid(const glm::vec2& pos)
	{
		if (std::find(m_AIPath.begin(), m_AIPath.end(), pos) != m_AIPath.end())
			return true;
		return false;
	}

	void SceneManager::AddSceneCollision(const glm::vec2& pos)
	{
		const glm::vec2 size = { 1, 1 };
		auto& tile(Application::Get().m_Assets->GetManager().AddEntity());
		tile.AddComponent<ColliderComponent>("terrain", pos, size);
		tile.AddGroup(GroupColliders);
	}

	void SceneManager::NewPosAIPath(const glm::vec2& pos)
	{
		if (!IsPositionValid(pos)) m_AIPath.push_back(pos);
	}

}