#pragma once
#include "gepch.h"

#include "GameEngine/Core/ECS/Components.h"
#include "GameEngine/Events/KeyEvent.h"
#include "GameEngine/KeyCodes.h"

namespace GameEngine
{
	class KeyboardController : public Component
	{
	public:

		void Init() override
		{
			if (!m_Entity->HasComponent<TransformComponent>())
				m_Entity->AddComponent<TransformComponent>();
			m_Transform = &m_Entity->GetComponent<TransformComponent>();
		}

		void OnEvent(Event& e) override
		{
			EventDispatcher dispatcher(e);
			dispatcher.Dispatch<KeyPressedEvent>(GE_BIND_EVENT_FN(KeyboardController::OnKeyPressedEvent));
			dispatcher.Dispatch<KeyReleasedEvent>(GE_BIND_EVENT_FN(KeyboardController::OnKeyReleasedEvent));
		}

		bool OnKeyPressedEvent(KeyPressedEvent& event)
		{
			if (event.GetKeyCode() == GE_KEY_W)
				m_Transform->velocity.y = -1;
			else if (event.GetKeyCode() == GE_KEY_S)
				m_Transform->velocity.y = 1;

			if (event.GetKeyCode() == GE_KEY_A)
				m_Transform->velocity.x = -1;
			else if (event.GetKeyCode() == GE_KEY_D)
				m_Transform->velocity.x = 1;

			return false;
		}

		bool OnKeyReleasedEvent(KeyReleasedEvent& event)
		{
			if (event.GetKeyCode() == GE_KEY_W)
				m_Transform->velocity.y = 0;
			else if (event.GetKeyCode() == GE_KEY_S)
				m_Transform->velocity.y = 0;

			if (event.GetKeyCode() == GE_KEY_A)
				m_Transform->velocity.x = 0;
			else if (event.GetKeyCode() == GE_KEY_D)
				m_Transform->velocity.x = 0;

			return false;
		}

	private:

		TransformComponent* m_Transform;

	};
}