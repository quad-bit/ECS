#pragma once
#include <stdint.h>
#include "EntityManager.h"


class World;
class Entity
{
private:

	uint32_t id;
	
	uint32_t GetId()
	{
		static uint32_t counter = 0;
		return counter++;
	}

public:

	Entity()
	{
		id = GetId();
		EntityManager::GetInstance()->HandleEntityCreation(this);
	}

	Entity(const Entity & e)
	{
		id = GetId();
		EntityManager::GetInstance()->HandleEntityDuplication(e, this);
	}

	uint32_t GetEntityId()
	{
		return id;
	}

	template <typename T>
	void AddComponent(T * component);

	template <typename T>
	std::vector<T*> GetComponents();

	template <typename T>
	T* GetComponent();
};


#include "World.h"

template<typename T>
inline void Entity::AddComponent(T * component)
{
	// Send the message to component manager via world
	World::GetInstance()->AddComponent<T>(this, component);
}

template<typename T>
inline std::vector<T*> Entity::GetComponents()
{
	return World::GetInstance()->GetComponents<T>(this);
}

template<typename T>
inline T * Entity::GetComponent()
{
	return World::GetInstance()->GetComponent<T>(this);;
}
