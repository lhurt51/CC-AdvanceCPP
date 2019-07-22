#pragma once

#include "GameEngine/Core.h"
#include "GameEngine/Core/ECS/ECS.h"
#include "GameEngine/Sprite.h"

#include <map>

namespace GameEngine
{
	class AssetManager
	{
	public:

		AssetManager(Manager* manager) : m_Manager(manager)
		{}
		~AssetManager() = default;

		void AddSprite(const std::string& id, const std::wstring& path);
		Sprite& GetSprite(const std::string& id);

	private:

		Manager* m_Manager;
		std::map<std::string, Sprite*> m_Sprites;

	};
}


