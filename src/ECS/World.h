#pragma once

#include <map>
#include <vector>
#include <memory>
#include "Component.h"

template <typename T>
class ComponentManager;
class BaseComponentManager;
class Entity;
class SystemBase;
class Component;

class World
{
private:
	// Singleton
	World() {}
	World(World const &) {}
	World const & operator= (World const &) {}
	static World * instance;

	std::map<ComponentType, std::shared_ptr<BaseComponentManager>> componentManagerMap;
	std::map<ComponentType, std::shared_ptr<SystemBase>> componentSystemMap;

	template <typename T>
	void CreateComponenHelper(Entity * entityObj, Component * src);

	template <typename T>
	void CreateComponenHelper(Entity * entityObj, const std::vector<Component *> & srcComponents);
	
public:
	void Init();
	void DeInit();
	void Update();
	static World* GetInstance();
	~World();

	template <typename T>
	void AddComponent(Entity * entityObj, T * component);

	template <typename T>
	std::vector<T*> GetComponents(Entity * entityObj);

	template <typename T>
	T* GetComponent(Entity * entityObj);

	void RegisterComponentManager(const ComponentType & type, std::shared_ptr<BaseComponentManager> manager);
	void RegisterComponentSystem(const ComponentType & type, std::shared_ptr<SystemBase> system);

	std::shared_ptr<BaseComponentManager> GetComponentManager(ComponentType type);

	template<typename T>
	std::shared_ptr<BaseComponentManager> GetComponentManager();
	
	std::shared_ptr<SystemBase> GetComponentSystem(ComponentType type);

	void GenerateComponents(Entity * entityObj, const std::map<ComponentType, std::vector<Component *>> & componentList);
};

#include "EntityManager.h"
#include "Entity.h"

template<typename T>
inline void World::CreateComponenHelper(Entity * entityObj, Component * src)
{
	T * obj(new T(*static_cast<T*>(src)));
	AddComponent<T>(entityObj, obj);
}

template<typename T>
inline void World::CreateComponenHelper(Entity * entityObj, const std::vector<Component*> & srcComponents)
{
	for each (Component* comp in srcComponents)
	{
		CreateComponenHelper<T>(entityObj, comp);
	}
}

template<typename T>
inline void World::AddComponent(Entity * entityObj, T * component)
{
	ComponentType compType = T::componentType;

	// this convertion looks ugly, need a better design for this scenario

	ComponentManager<T> * componentManger = static_cast<ComponentManager<T>*>(componentManagerMap[compType].get());
	//ComponentManager<T> * componentManger = (ComponentManager<T> *)(componentManagerMap[compType].get());
	componentManger->AddComponent(entityObj->GetEntityId(), component);

	EntityManager::GetInstance()->ComponentAdditionNotification(entityObj, component, compType);
}

template<typename T>
inline std::vector<T*> World::GetComponents(Entity * entityObj)
{
	assert(0 && "yet to be implemented");
	return std::vector<T*>();
}

template<typename T>
inline T * World::GetComponent(Entity * entityObj)
{
	ComponentType compType = T::componentType;
	T * component = static_cast<T*>( EntityManager::GetInstance()->GetComponent(entityObj->GetEntityId(), compType)[0]);
	
	return component;
}

template<typename T>
inline std::shared_ptr<BaseComponentManager> World::GetComponentManager()
{
	ComponentType type = T::componentType;
	return componentManagerMap[type];
}
