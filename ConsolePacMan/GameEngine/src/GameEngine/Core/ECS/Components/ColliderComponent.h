#pragma once
#include "gepch.h"

#include "GameEngine/Core/TimeStep.h"
#include "GameEngine/Core/ECS/Components.h"

namespace GameEngine
{
	class ColliderComponent : public Component
	{
	public:

		ColliderComponent(std::string t)
		{
			tag = t;

			collider.pos = { 0 };
			collider.size = { 1 };
		}

		ColliderComponent(std::string t, const glm::vec2& pos, const glm::vec2& size)
		{
			tag = t;

			collider.pos = pos;
			collider.size = size;
		}

		~ColliderComponent()
		{
			// maybe destroy
		}

		void Init() override
		{
			if (!m_Entity->HasComponent<TransformComponent>())
				m_Entity->AddComponent<TransformComponent>();
			transform = &m_Entity->GetComponent<TransformComponent>();

			if (!m_Entity->HasComponent<SpriteComponent>())
				m_Entity->AddComponent<SpriteComponent>();
			spriteInfo = &m_Entity->GetComponent<SpriteComponent>().sprite;

			// sprite = SpriteManager::LoadSprite();
		}

		void Update(TimeStep ts) override
		{
			if (tag != "terrain")
			{
				collider.pos = static_cast<glm::vec2>(transform->position);
				collider.size = static_cast<glm::vec2>(spriteInfo->size * transform->scale);
			}
		}

	public:

		struct Collider
		{
			glm::vec2 pos;
			glm::vec2 size;
		};

	public:

		Collider collider;
		std::string tag;

		SpriteInfo* spriteInfo;
		TransformComponent* transform;


	};
}

