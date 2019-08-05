#pragma once
#include "gepch.h"

#include "GameEngine/Core/TimeStep.h"
#include "GameEngine/Core/ECS/Components.h"

#include <glm/glm.hpp>

namespace GameEngine
{
	class TransformComponent : public Component
	{
	public:

		TransformComponent(float inSpeed = 10.0f)
		{
			position = { 0.0f };
			scale = { 1.0f };
			rotation = 0.0f;
			speed = inSpeed;
		}

		TransformComponent(const glm::vec2& pos, float inSpeed = 10.0f)
		{
			position = pos;
			scale = { 1.0f };
			rotation = 0.0f;
			speed = inSpeed;
		}

		TransformComponent(const glm::vec2& pos, const glm::vec2& sc, float rot = 0.0f, float inSpeed = 10.0f)
		{
			position = pos;
			scale = sc;
			rotation = rot;
			speed = inSpeed;
		}

		void Init() override
		{
			velocity = { 0 };
		}

		void Update(TimeStep ts) override
		{
			position = position + velocity * speed * (float)ts;
		}

	public:

		glm::vec2 position;
		glm::vec2 scale;
		float rotation;

		glm::vec2 velocity;
		float speed;

	};
}
