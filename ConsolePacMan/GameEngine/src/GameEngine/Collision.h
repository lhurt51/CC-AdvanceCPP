#pragma once

#include <glm/glm.hpp>

namespace GameEngine
{

	class ColliderComponent;

	class Collision
	{
	public:

		static bool AABB(const glm::vec2& pos1, const glm::vec2& size1, const glm::vec2& pos2, const glm::vec2& size2);
		static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);

	};
}

