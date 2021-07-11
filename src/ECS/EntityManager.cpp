#include <memory>
#include <stdio.h>
#include <assert.h>

#include "EntityManager.h"
#include "Entity.h"

EntityManager * EntityManager::instance = nullptr;

void EntityManager::Init()
{
}

void EntityManager::DeInit()
{
}

void EntityManager::Update()
{
}

EntityManager * EntityManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new EntityManager();
	}
	return instance;
}

EntityManager::~EntityManager()
{
}

void EntityManager::HandleEntityCreation(Entity * entityObj)
{
	std::shared_ptr<EntityWrapper> temp(new EntityWrapper(entityObj));
	wrapperMap.insert(std::pair< uint32_t, std::shared_ptr<EntityWrapper>>({ entityObj->GetEntityId(), temp }));
}

void EntityManager::HandleEntityDuplication(const Entity & src, Entity * dest)
{
	// Create all components of the source
	std::shared_ptr<EntityWrapper> temp(new EntityWrapper(dest));
	wrapperMap.insert(std::pair< uint32_t, std::shared_ptr<EntityWrapper>>({ dest->GetEntityId(), temp }));

	std::shared_ptr<EntityWrapper> srcWrapper = wrapperMap[const_cast<Entity&>(src).GetEntityId()];

	std::map<ComponentType, std::vector<Component *>> enitityComponentList = srcWrapper->enitityComponentList;

	World::GetInstance()->GenerateComponents(dest, enitityComponentList);
}

void EntityManager::ComponentAdditionNotification(Entity * entityObj, Component * component, ComponentType type)
{
	/////////////////////////////////////////////////////////////////////////////////////////
	// MULTIPLE COMPONENTS OF SAME TYPE CAN BE ADDED TO AN ENTITY ..!!!!!!!!!!!!!!
	////////////////////////////////////////////////////////////////////////////////////////

	//printf("Component Addition %i\n", entityObj->GetEntityId());

	std::shared_ptr<EntityWrapper> wrapper = wrapperMap[entityObj->GetEntityId()];
	
	// search for the compoenent type in the map
	if (wrapper->enitityComponentList.find(type) != wrapper->enitityComponentList.end())
	{
		// if it exists then add the newly added component
		wrapper->enitityComponentList[type].push_back(component);
	}
	else
	{
		// if the component type is not found, create a map entry for the type
		wrapper->enitityComponentList.insert(std::pair<ComponentType, std::vector<Component *>>({ type, std::vector<Component*> {component} }));
	}
}

std::vector<Component*> EntityManager::GetComponent(const uint32_t & id, const ComponentType & type)
{
	std::shared_ptr<EntityWrapper> wrapper = wrapperMap[id];
	std::vector<Component*> componentList;

	// search for the compoenent type in the map
	if (wrapper->enitityComponentList.find(type) != wrapper->enitityComponentList.end())
	{
		componentList = wrapper->enitityComponentList[type];
	}
	
	if(componentList.size() == 0)
	{
		// if the component type is not found assert
		assert(0 && "component not found on the entity");
	}

	return componentList;
}
