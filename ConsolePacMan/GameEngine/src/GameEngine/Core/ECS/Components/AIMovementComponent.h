#pragma once
#include "gepch.h"

#include "GameEngine/Core/TimeStep.h"
#include "GameEngine/Core/ECS/Components.h"

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
		}

		void Update(TimeStep ts) override
		{
			glm::vec2 targetPos = m_PlayerTransform.position;

		}

	private:

		void AIStage1()
		{

		}

		void AIStage2()
		{

		}

	private:

		bool bIsStage1 = true;
		TransformComponent& m_PlayerTransform;
		TransformComponent* m_Transform;

	};
}