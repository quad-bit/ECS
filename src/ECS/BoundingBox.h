#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <vector>
#include <assert.h>

#include "Rect2D.h"

class AABB;
class OBB;

enum class BoxType
{
	AABB,
	OBB
};

template <typename T>
class BoundingBox
{
private:
	T * boxObject;
	BoxType boxType;

	Rect2D boxRect;

	void CalculateBoxRect(const glm::vec2 * meshData, const uint32_t & count, const glm::mat4 & transformationMat);

public:

	~BoundingBox()
	{

	}

	BoundingBox();
	Rect2D CalculateBoundingBox(const glm::vec2 * meshData, const uint32_t & count, const glm::mat4 & transformationMat);
};

#include "AABB.h"

template<typename T>
inline void BoundingBox<T>::CalculateBoxRect(const glm::vec2 * meshData, const uint32_t & count, const glm::mat4 & transformationMat)
{
	// find the min max coords using the world coordinates
	float minX, maxX;
	float minY, maxY;

	glm::vec4 pos = transformationMat * glm::vec4(meshData[0].x, meshData[0].y, 0, 1);

	minX = maxX = pos.x;
	minY = maxY = pos.y;

	for (uint32_t i = 1; i < count; i++)
	{
		pos = transformationMat * glm::vec4(meshData[i].x, meshData[i].y, 0, 1);

		// x-axis
		if (pos.x < minX)
			minX = pos.x;
		if (pos.x > maxX)
			maxX = pos.x;

		// y-axis
		if (pos.y < minY)
			minY = pos.y;
		if (pos.y > maxY)
			maxY = pos.y;
	}

	// Create the box rect using min and max
	{
		boxRect.bottomLeft.x = minX;
		boxRect.bottomLeft.y = minY;

		boxRect.topLeft.x = minX;
		boxRect.topLeft.y = maxY;

		boxRect.bottomRight.x = maxX;
		boxRect.bottomRight.y = minY;

		boxRect.topRight.x = maxX;
		boxRect.topRight.y = maxY;

		boxRect.minX = minX;
		boxRect.maxX = maxX;
		boxRect.minY = minY;
		boxRect.maxY = maxY;
	}
}

template<>
inline BoundingBox<AABB>::BoundingBox()
{
	boxType = BoxType::AABB;
}

template<>
inline BoundingBox<OBB>::BoundingBox()
{
	boxType = BoxType::OBB;
}

template<>
inline Rect2D BoundingBox<AABB>::CalculateBoundingBox(const glm::vec2 * meshData, const uint32_t & count, const glm::mat4 & transformationMat)
{
	CalculateBoxRect(meshData, count, transformationMat);
	boxObject->UpdateBoxRect(boxRect);
	return boxRect;
}

template<>
inline Rect2D BoundingBox<OBB>::CalculateBoundingBox(const glm::vec2 * meshData, const uint32_t & count, const glm::mat4 & transformationMat)
{
	assert(0 && "not yet implemented");
	return boxRect;
}