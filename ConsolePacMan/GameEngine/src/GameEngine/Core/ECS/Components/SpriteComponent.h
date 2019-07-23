#pragma once

#include "GameEngine/Core/ECS/Components.h"
#include "GameEngine/Managers/AssetManager.h"
#include "GameEngine/Application.h"

#include "GameEngine/Sprite.h"

namespace GameEngine
{
	class SpriteComponent : public Component
	{
	public:

		SpriteComponent() = default;
		SpriteComponent(std::string id) { SetSprite(id); }
		~SpriteComponent() = default;

		void SetSprite(std::string id) { m_Sprite = Application::Get().m_Assets->GetSprite(id); }

		void Init() override
		{
			if (!m_Entity->HasComponent<TransformComponent>())
			{
				m_Entity->AddComponent<TransformComponent>();
			}
			m_Transform = &m_Entity->GetComponent<TransformComponent>();
		}

		void Update(TimeStep ts) override
		{

		}

		void OnDraw() override
		{
			// SpriteManager::Draw(transform, spriteInfo)
		}

	private:

		TransformComponent* m_Transform;
		Sprite m_Sprite;

	};
}