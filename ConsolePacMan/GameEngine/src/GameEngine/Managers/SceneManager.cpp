#include "gepch.h"
#include "SceneManager.h"

#include "GameEngine/Application.h"
#include "GameEngine/Managers/AssetManager.h"

namespace GameEngine
{

	void SceneManager::LoadScene(const std::string& path, const glm::vec2& pos)
	{
		SpriteInfo& map = Application::Get().m_Assets->GetSprite(path);
		for (int y = 0; y < map.size.y; y++)
		{
			for (int x = 0; x < map.size.x; x++)
			{
				if (map.GetGlyph(x, y) != L'.' && map.GetGlyph(x, y) != L'o')
				{
					glm::vec2 tmp = { pos.x + x, pos.y + y };
					AddSceneCollision(tmp);
				}
			}
		}
	}

	void SceneManager::AddSceneCollision(const glm::vec2& pos)
	{
		const glm::vec2 size = { 1, 1 };
		auto& tile(Application::Get().m_Assets->GetManager().AddEntity());
		tile.AddComponent<ColliderComponent>("terrain", pos, size);
		tile.AddGroup(GroupColliders);
	}

}