#pragma once
#include "Component.h"
#include <glm/glm.hpp>

#include <vector>

class MeshFilter : public Component
{
private:
	std::vector<glm::vec2> vertices;

public:

	// This is ugly
	static ComponentType const componentType = ComponentType::MESHFILTER;

	MeshFilter()
	{
		
	}

	MeshFilter(glm::vec2 * verts, const uint32_t & count)
	{
		vertices.resize(count);
		for (uint32_t i = 0; i < count; i++)
		{
			vertices[i] = verts[i];
		}
	}

	const std::vector<glm::vec2> GetVertices()
	{
		return vertices;
	}
};

