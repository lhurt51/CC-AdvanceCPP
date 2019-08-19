#pragma once
#include "gepch.h"

#include "GameEngine/Core/TimeStep.h"
#include "GameEngine/Core/ECS/Components.h"
#include "GameEngine/Managers/SceneManager.h"

namespace GameEngine
{
	class AIMovementComponent : public Component
	{
	public:

		AIMovementComponent() = default;
		AIMovementComponent(TransformComponent& playerTransform) : m_PlayerTransform(playerTransform) {}
		~AIMovementComponent() = default;

		void Init() override
		{
			if (!m_Entity->HasComponent<TransformComponent>())
				m_Entity->AddComponent<TransformComponent>();
			m_Transform = &m_Entity->GetComponent<TransformComponent>();
			m_Transform->speed = 2.0f;
		}

		void Update(TimeStep ts) override
		{
			// glm::vec2 targetPos = m_PlayerTransform.position;
			if (bIsStage1) AIStage1();
			else AIStage2();
		}

	private:

		void AIStage1()
		{
			if (m_Transform->velocity.y != -1.0f) m_Transform->velocity.y = -1;
			if (SceneManager::IsPositionValid(m_Transform->position))
			{
				bIsStage1 = false;
				AIStage2();
			}
		}

		void AIStage2()
		{
			static glm::bvec4 lastDir(false, false, false, false);
			glm::bvec4 dir(false, false, false, false);

			if (SceneManager::IsPositionValid(glm::trunc(m_Transform->position) + glm::vec2(-1.0f, 0.0f)))
				dir.r = true;
			if (SceneManager::IsPositionValid(glm::trunc(m_Transform->position) + glm::vec2(0.0f, -1.0f)))
				dir.g = true;
			if (SceneManager::IsPositionValid(glm::trunc(m_Transform->position) + glm::vec2(1.0f, 0.0f)))
				dir.b = true;
			if (SceneManager::IsPositionValid(glm::trunc(m_Transform->position) + glm::vec2(0.0f, 1.0f)))
				dir.a = true;

			if (dir != lastDir)
			{
				glm::vec2 lastVel = m_Transform->velocity;
				m_Transform->velocity = glm::vec2(0.0f, 0.0f);
				if (dir.b && lastVel.x != -1.0f)
				{
					m_Transform->velocity.x = 1.0f;
				}
				else if (dir.a && lastVel.y != -1.0f)
				{
					m_Transform->velocity.y = 1.0f;
				}
				else if (dir.g && lastVel.y != 1.0f)
				{
					m_Transform->velocity.y = -1.0f;
				}
				else if (dir.r && lastVel.x != 1.0f)
				{
					m_Transform->velocity.x = -1.0f;
				}
			}
			lastDir = dir;
		}

	private:

		bool bIsStage1 = true;
		TransformComponent& m_PlayerTransform;
		TransformComponent* m_Transform;

	};
}