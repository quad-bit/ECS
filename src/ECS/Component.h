#pragma once


enum class ComponentType
{
	TRANSFORM,
	COLLIDER,
	MESHFILTER,
	HEALTH,
	ATTACK
};

class Component
{
private:

public:
	virtual ~Component()
	{

	}
};
