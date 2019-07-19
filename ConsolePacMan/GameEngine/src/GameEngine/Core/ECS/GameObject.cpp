#include "gepch.h"
#include "GameObject.h"

#include "Component.h"

namespace GameEngine
{

	/*
	GameObject::~GameObject()
	{
		for (unsigned int i = 0; i < m_Components.size(); i++)
			if (m_Components[i])
				delete m_Components[i];

		for (unsigned int i = 0; i < m_Children.size(); i++)
			if (m_Children[i])
				delete m_Children[i];
	}

	GameObject& GameObject::AddChild(GameObject* child)
	{
		m_Children.push_back(child);
		child->GetTransform()->SetParent(&m_Transform);
		return *this;
	}

	GameObject& GameObject::AddComponent(Component* component)
	{
		m_Components.push_back(component);
		component->SetParent(this);
		return *this;
	}

	void GameObject::OnEvent(Event& e)
	{
		OnEventAll(e);
	}

	void GameObject::OnUpdate(TimeStep ts)
	{
		OnUpdateAll(ts);
	}

	std::vector<GameObject*> GameObject::GetAllAttached()
	{
		return std::vector<GameObject*>();
	}

	void GameObject::OnEventAll(Event& e)
	{
		for (unsigned int i = 0; i < m_Children.size(); i++)
		{
			m_Children[i]->OnEvent(e);
		}

		/*
		for (unsigned int i = 0; i < m_Components.size(); i++)
		{
			m_Components[i]->OnEvent(e);
		}
		*\/
	}

	void GameObject::OnUpdateAll(TimeStep ts)
	{
		for (unsigned int i = 0; i < m_Children.size(); i++)
		{
			m_Children[i]->OnUpdate(ts);
		}

		/*
		for (unsigned int i = 0; i < m_Components.size(); i++)
		{
			m_Components[i]->OnUpdate(ts);
		}
		*\/
	}
	*/

}