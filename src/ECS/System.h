#pragma once

#include "Component.h"
#include <vector>
#include <memory>

class BaseComponentManager;

class SystemBase
{
private:

protected:
	
	// Collider will require Transform and MeshFilter
	std::vector<ComponentType> dependencyList;
	std::shared_ptr<BaseComponentManager> componentManager;

public:
	virtual void Init() {}
	virtual void Update() {}
	virtual void DeInit() {}

	virtual ~SystemBase() {}
};
