#pragma once

#include "Component.h"

class Health : public Component
{
private:
	int m_health = 0;

public:
	// This is ugly
	static ComponentType const componentType = ComponentType::HEALTH;
};