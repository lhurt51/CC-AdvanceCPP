#pragma once

#include "GameEngine/Core.h"
#include "GameEngine/Core/TimeStep.h"
#include "GameEngine/Events/Event.h"
#include "GameEngine/Core/ECS/GameObject.h"

namespace GameEngine
{
	class Layer
	{
	public:

		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(TimeStep ts) { m_Root.OnUpdate(ts); }
		virtual void OnEvent(Event& e) { m_Root.OnEvent(e); }

		inline const std::string& GetName() const { return m_DebugName; }

		inline void AddObjToScene(GameObject* child) { m_Root.AddChild(child); }

	protected:

		GameObject m_Root;
		std::string m_DebugName;

	};
}


