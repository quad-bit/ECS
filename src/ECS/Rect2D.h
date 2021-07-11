#pragma once

#include <glm/glm.hpp>

class Rect2D
{
private:

public:
	glm::vec2 topLeft, topRight, bottomLeft, bottomRight;
	float minX, maxX, minY, maxY;
	Rect2D() {}

	Rect2D(const glm::vec2 & topLeft, const glm::vec2 & topRight, const glm::vec2 & bottomLeft, const glm::vec2 & bottomRight)
	{
		(this)->bottomLeft = bottomLeft;
		(this)->bottomRight = bottomRight;
		(this)->topLeft = topLeft;
		(this)->topRight = topRight;
	}

};