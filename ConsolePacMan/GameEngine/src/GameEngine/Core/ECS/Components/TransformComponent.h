#pragma once

#include "GameEngine/Core/TimeStep.h"
#include "GameEngine/Core/ECS/Components.h"

#include <glm/glm.hpp>

namespace GameEngine
{
	class TransformComponent : public Component
	{
	public:

		TransformComponent()
		{
			position = { 0 };
			scale = { 1 };
		}

		TransformComponent(const glm::vec2& pos)
		{
			position = pos;
			scale = { 1 };
		}

		TransformComponent(const glm::vec2& pos, const glm::vec2& sc, float rot = 0.0f)
		{
			position = pos;
			scale = sc;
			rotation = rot;
		}

		void Init() override
		{
			velocity = { 0 };
		}

		void Update(TimeStep ts) override
		{
			position = (position + velocity) * (float)ts;
		}

	public:

		glm::vec2 position;
		glm::vec2 scale;
		float rotation = 0.0f;

		glm::vec2 velocity;

	};
}
