#include "gepch.h"
#include "Collision.h"

#include "Core/ECS/Components/ColliderComponent.h"

namespace GameEngine
{
	bool Collision::AABB(const glm::vec2& pos1, const glm::vec2& size1, const glm::vec2& pos2, const glm::vec2& size2)
	{
		if ((int)(pos1.x) == (int)(pos2.x) &&
			(int)(pos2.x) == (int)(pos1.x) &&
			(int)(pos1.y) == (int)(pos2.y) &&
			(int)(pos2.y) == (int)(pos1.y))
			return true;
		return false;
	}

	bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB)
	{
		if (AABB(colA.collider.pos, colA.collider.size, colB.collider.pos, colB.collider.size))
			return true;
		return false;
	}
}
