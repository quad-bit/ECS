#pragma once
#include <map>
#include "Component.h"
#include <vector>

class Entity;

class EntityWrapper
{
private:
	Entity * entityObj;
	std::map<ComponentType, std::vector<Component *>> enitityComponentList;

protected:

public:
	EntityWrapper(Entity * entity) : entityObj(entity) {}
	friend class EntityManager;
};

class EntityManager
{
private:
	// Singleton
	EntityManager() {}
	EntityManager(EntityManager const &) {}
	EntityManager const & operator= (EntityManager const &) {}
	static EntityManager * instance;

	std::map<uint32_t, std::shared_ptr<EntityWrapper>> wrapperMap;

public:
	void Init();
	void DeInit();
	void Update();
	static EntityManager* GetInstance();
	~EntityManager();

	void HandleEntityCreation(Entity * entityObj);
	void HandleEntityDuplication(const Entity & src, Entity * dest);

	void ComponentAdditionNotification(Entity * entityObj, Component * component, ComponentType type);

	std::vector<Component*> GetComponent(const uint32_t & id, const ComponentType & type);
};

