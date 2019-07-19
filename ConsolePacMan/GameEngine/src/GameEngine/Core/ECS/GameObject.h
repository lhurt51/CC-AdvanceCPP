#pragma once

#include "GameEngine/Core.h"
#include "GameEngine/Events/Event.h"
#include "GameEngine/Core/TimeStep.h"
#include "Transform.h"

#include <vector>

namespace GameEngine
{

	/*
	class Component;

	class GameObject
	{
	public:

		GameObject(const glm::vec2& pos = { 0, 0 })
		{}
		virtual ~GameObject();

		GameObject& AddChild(GameObject* child);
		GameObject& AddComponent(Component* component);

		virtual void OnEvent(Event& e);
		virtual void OnUpdate(TimeStep ts);

		std::vector<GameObject*> GetAllAttached();

		inline Transform* GetTransform() { return &m_Transform; }

	private:

		void OnEventAll(Event& e);
		void OnUpdateAll(TimeStep ts);

	private:

		std::vector<GameObject*> m_Children;
		std::vector<Component*> m_Components;
		Transform m_Transform;

	};
	*/
}

