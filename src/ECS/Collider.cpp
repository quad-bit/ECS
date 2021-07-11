#include "Collider.h"
#include <assert.h>

Rect2D Collider2D::GetBoxRect(const glm::vec2 * meshData, const uint32_t & count, const glm::mat4 & transformationMat)
{
	if (boxType == BoxType::AABB)
	{
		return boundingBoxAABB->CalculateBoundingBox(meshData, count, transformationMat);
	}

	assert(0 && "invalid type");
	return Rect2D();
}
