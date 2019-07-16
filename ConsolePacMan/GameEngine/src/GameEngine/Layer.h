#pragma once

#include "GameEngine/Core.h"
#include "GameEngine/Core/TimeStep.h"
#include "GameEngine/Events/Event.h"

namespace GameEngine
{
	class Layer
	{
	public:

		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(TimeStep ts) {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }

	protected:

		std::string m_DebugName;

	};
}


