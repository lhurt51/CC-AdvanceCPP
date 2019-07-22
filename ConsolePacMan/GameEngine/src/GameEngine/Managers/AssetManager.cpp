#include "gepch.h"
#include "AssetManager.h"

namespace GameEngine
{

	void AssetManager::AddSprite(const std::string& id, const std::wstring& path)
	{
		m_Sprites.emplace(id, new Sprite(path));
	}

	Sprite& AssetManager::GetSprite(const std::string& id)
	{
		return *m_Sprites[id];
	}

}