#pragma once
#include "gepch.h"

#include "Transform.h"
#include "GameObject.h"

namespace GameEngine
{
	class Component
	{
	public:

		Component() : m_Parent(0)
		{}
		virtual ~Component() = default;

		virtual void OnEvent(Event& e) {}
		virtual void OnUpdate(TimeStep ts) {}

		inline Transform* GetTransform() { return m_Parent->GetTransform(); }
		inline const Transform& GetTransform() const { return *m_Parent->GetTransform(); }

		virtual void SetParent(GameObject* parent) { m_Parent = parent; }

	private:

		GameObject* m_Parent;

	};
}