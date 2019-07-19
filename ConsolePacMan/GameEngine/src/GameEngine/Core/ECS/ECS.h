#pragma once

#include "gepch.h"

#include "GameEngine/Core/TimeStep.h"
#include "GameEngine/Events/Event.h"

#include <bitset>


namespace GameEngine
{
	class Component;
	class Entity;
	class Manager;

	// Defining the unique component ID
	using ComponentID = std::size_t;
	using Group = std::size_t;

	// Incrementing the componentTypeID each new Component
	inline ComponentID GetNewComponentTypeID()
	{
		static ComponentID lastID = 0u;
		return lastID++;
	}

	// Setting the type ID base on type of component
	template<typename T> inline ComponentID GetComponentTypeID() noexcept
	{
		static_assert(std::is_base_of<Component, T>::value, "");
		static ComponentID typeID = GetNewComponentTypeID();
		return typeID;
	}

	// Setting a maximum amount of components
	constexpr std::size_t maxComponents = 32;
	constexpr std::size_t maxGroups = 32;

	// To check if object has component type
	using ComponentBitSet = std::bitset<maxComponents>;
	// To check if object has group type
	using GroupBitSet = std::bitset<maxGroups>;
	// Array to store pointers to the components
	using ComponentArray = std::array<Component*, maxComponents>;

	// A base component class
	class Component
	{
	public:

		virtual ~Component() = default;

		virtual void Init() {}
		virtual void Update(TimeStep ts) {}
		virtual void OnEvent(Event& e) {}
		virtual void OnDraw() {}

	public:

		Entity* m_Entity;

	};

	// Base entity class that owns an array of components
	class Entity
	{
	public:

		Entity(Manager& manager) : m_Manager(manager)
		{}

		bool IsActive() const { return m_bIsActive; }

		virtual void Update(TimeStep ts)
		{
			for (auto& c : m_Components) c->Update(ts);
		}

		virtual void OnEvent(Event& e)
		{
			for (auto& c : m_Components) c->OnEvent(e);
		}

		virtual void OnDraw()
		{
			for (auto& c : m_Components) c->OnDraw();
		}

		inline void Destroy() { m_bIsActive = false; }

		inline void AddGroup(Group group); // { m_GroupBitSet[group] = true; m_Manager.addToGroup(this, group); }
		inline bool HasGroup(Group group) const { return m_GroupBitSet[group]; }
		inline void DeleteGroup(Group group) { m_GroupBitSet[group] = false; }

		template<typename T> inline bool HasComponent() const { return m_ComponentBitSet[GetComponentTypeID<T>()]; }

		template<typename T, typename... TArgs>
		T& AddComponent(TArgs&&... args)
		{
			T* c(new T(std::forward<TArgs>(args)...));
			c->m_Entity = this;
			std::unique_ptr<Component> uPtr{ c };
			m_Components.emplace_back(std::move(uPtr));

			m_ComponentArray[GetComponentTypeID<T>()] = c;
			m_ComponentBitSet[GetComponentTypeID<T>()] = true;

			c->Init();
			return *c;
		}

		template<typename T> inline T& GetComponent() const
		{
			auto ptr(m_ComponentArray[GetComponentTypeID<T>()]);
			return *static_cast<T*>(ptr);
		}

	private:

		Manager& m_Manager;
		bool m_bIsActive = true;
		std::vector<std::unique_ptr<Component>> m_Components;

		ComponentArray m_ComponentArray;
		ComponentBitSet m_ComponentBitSet;
		GroupBitSet m_GroupBitSet;

	};

	class Manager
	{
	public:



	private:

		std::vector<std::unique_ptr<Entity>> m_Entities;
		std::array<std::vector<Entity*>, maxGroups> m_GroupedEntities;

	};

}