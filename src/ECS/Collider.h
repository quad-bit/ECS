#pragma once
#include "Component.h"
#include "BoundingBox.h"

class AABB;
class OBB;

struct Collision
{
	uint32_t entityId_0, entityId_1;
	Rect2D box0, box1;
};

class Collider2D : public Component
{
private:
	BoxType boxType;
	BoundingBox<AABB> * boundingBoxAABB;
	BoundingBox<OBB> * boundingBoxOBB;

public:

	// This is ugly
	static ComponentType const componentType = ComponentType::COLLIDER;

	Collider2D()
	{
		boxType = BoxType::AABB;
		boundingBoxAABB = new BoundingBox<AABB>();
	}

	Collider2D(const Collider2D & col)
	{
		boxType = BoxType::AABB;
		boundingBoxAABB = new BoundingBox<AABB>();
		*boundingBoxAABB = *col.boundingBoxAABB;
	}

	~Collider2D()
	{
		delete boundingBoxAABB;
	}

	Rect2D GetBoxRect(const glm::vec2 * meshData, const uint32_t & count, const glm::mat4 & transformationMat);
};
