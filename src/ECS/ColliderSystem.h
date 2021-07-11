#pragma once
#pragma once

#include "System.h"
#include "Collider.h"

class BaseComponentManager;

typedef void(*callBackPtr)(std::vector<Collision>);

class ColliderSystem : public SystemBase
{
private:
	std::shared_ptr <BaseComponentManager> transformCompManager, meshfilterCompManager;
	std::vector<Collision> CheckForCollision(const std::vector<std::tuple<uint32_t, Rect2D>> & boxList);

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void DeInit() override;

	static callBackPtr callBack;
};

