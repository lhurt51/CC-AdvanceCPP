#pragma once

#include "GameEngine/Core.h"
#include "GameEngine/Events/Event.h"
#include "GameEngine/Core/TimeStep.h"

#include <vector>
#include <glm/glm.hpp>

class Component;

namespace GameEngine
{
	class GameObject
	{
	public:

		GameObject(const glm::vec2& pos = { 0, 0 })
		{}
		virtual ~GameObject();

		GameObject* AddChild(GameObject* child);

	private:

		std::vector<GameObject*> m_Children;
		std::vector<Component*> m_Components;

	};
}

