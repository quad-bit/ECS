#pragma once

#include "Component.h"

class Attack : public Component
{
private:
	unsigned int m_attackPower = 0;

public:
	// This is ugly
	static ComponentType const componentType = ComponentType::ATTACK;

};