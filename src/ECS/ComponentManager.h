#pragma once

#include "Component.h"
#include <vector>
#include <map>
#include <memory>

class BaseComponentManager
{
private:


protected:
	std::vector<Component*> componentList;
	//std::map<uint32_t, Component*> idToComponentMap;

	std::map<Component*, uint32_t> componentToIdMap;

	ComponentType componentType;

public:
	virtual ~BaseComponentManager()
	{

	}

	BaseComponentManager(ComponentType type)
	{
		componentType = type;
	}

	ComponentType GetManagerType()
	{
		return componentType;
	}

	std::vector<Component*> & GetComponentList()
	{
		return componentList;
	}

	const std::map<Component*, uint32_t> & GetComponentMap()
	{
		return componentToIdMap;
	}

	virtual void AddComponent(const uint32_t & entityId, Component * component) {}

};

template <typename T>
class ComponentManager : public BaseComponentManager
{
private:

public:
	ComponentManager(ComponentType type) : BaseComponentManager(type)
	{

	}

	void AddComponent(const uint32_t & entityId, Component * component) override;
};

template<typename T>
inline void ComponentManager<T>::AddComponent(const uint32_t & entityId, Component * component)
{
	componentList.push_back(component);

	componentToIdMap.insert(std::pair<Component*, uint32_t>({ component, entityId }));
}
