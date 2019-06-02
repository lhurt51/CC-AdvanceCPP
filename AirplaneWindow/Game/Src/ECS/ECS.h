#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class Manager;

// Defining unique component ID
using ComponentID = std::size_t;
using Group = std::size_t;

// Incrementing the componentTypeID each new Component
inline ComponentID getNewComponentTypeID()
{
	static ComponentID lastID = 0u;
	return lastID++;
}

// Setting the type ID base on type of component
template<typename T> inline ComponentID getComponentTypeID() noexcept
{
	static_assert(std::is_base_of<Component, T>::value, "");
	static ComponentID typeID = getNewComponentTypeID();
	return typeID;
}

// Setting a maximum amount of components
constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

// To check if object has component type
using ComponentBitSet = std::bitset<maxComponents>;
// To check if object has component type
using GrouptBitSet = std::bitset<maxGroups>;
// Array to store pointers to the components
using ComponentArray = std::array<Component*, maxComponents>;

// A base component class
class Component
{
public:
	Entity* entity;

	virtual ~Component() {}

	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}
};

// Base entity class that owns an array of components
class Entity
{
	Manager& manager;
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
	GrouptBitSet groupBitSet;

public:

	Entity(Manager& mManager) : manager(mManager) {}

	bool isActive() const { return active; }

	void update()
	{
		for (auto& c : components) c->update();
	}

	void draw()
	{ 
		for (auto& c : components) c->draw();
	}

	void destroy() { active = false; }

	bool hasGroup(Group mGroup)
	{
		return groupBitSet[mGroup];
	}

	void addGroup(Group mGroup);

	void delGroup(Group mGroup)
	{
		groupBitSet[mGroup] = false;
	}

	template<typename T> bool hasComponent() const
	{
		return componentBitSet[getComponentTypeID<T>()];
	}

	template<typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		c->init();
		return *c;
	}

	template<typename T> T& getComponent() const
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

};

class Manager
{

	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;

public:

	void update()
	{
		for (auto& e : entities) e->update();
	}

	void draw()
	{
		for (auto& e : entities) e->draw();
	}

	void refresh()
	{
		for (auto i(0u); i < maxGroups; i++)
		{
			auto& v(groupedEntities[i]);
			v.erase(
				std::remove_if(std::begin(v), std::end(v),
					[i](Entity* mEntity)
			{
				return !mEntity->isActive() || !mEntity->hasGroup(i);
			}), std::end(v));
		}

		entities.erase(std::remove_if(std::begin(entities), std::end(entities), 
			[](const std::unique_ptr<Entity> &mEntity)
		{
			return !mEntity->isActive();
		}), std::end(entities));
	}

	void addToGroup(Entity* mEntity, Group mGroup)
	{
		groupedEntities[mGroup].emplace_back(mEntity);
	}

	std::vector<Entity*>& getGroup(Group mGroup)
	{
		return groupedEntities[mGroup];
	}

	Entity& addEntity()
	{
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}
};
