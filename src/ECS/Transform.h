#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "Component.h"

class Transform2D : public Component
{
private:

	void UpdateTransformation()
	{
		T = glm::translate(glm::vec3(position.x, position.y, 0));
		S = glm::scale(glm::vec3(scale.x, scale.y, 1));

		glm::mat4 rotXMat = glm::rotate(rotation.x, glm::vec3(1, 0, 0));
		glm::mat4 rotYMat = glm::rotate(rotation.y, glm::vec3(0, 1, 0));
		glm::mat4 rotZMat = glm::rotate(0.0f, glm::vec3(0, 0, 1));

		R = rotZMat * rotYMat * rotXMat;

		transformationMat = T * R * S;
	}
	
	glm::vec2 position;
	glm::vec2 scale;
	glm::vec2 rotation;

	glm::mat4 T, R, S;
	glm::mat4 transformationMat;

	void Init(glm::vec2 position, glm::vec2 scale, glm::vec2 rotation)
	{
		transformationMat = glm::identity<glm::mat4>();

		//componentType = ComponentType::TRANSFORM;
		this->position = position;
		this->scale = scale;
		this->rotation = rotation;

		UpdateTransformation();
	}

public:
	// This is ugly
	static ComponentType const componentType = ComponentType::TRANSFORM;

	Transform2D()
	{
		Init(glm::vec2(0,0), glm::vec2(1, 1), glm::vec2(0, 0));
	}

	Transform2D(const glm::vec2 & pos)
	{
		Init(pos, glm::vec2(1, 1), glm::vec2(0, 0));
	}

	void SetPosition(const glm::vec2 & pos)
	{
		position = pos;
		UpdateTransformation();
	}

	void SetScale(const glm::vec2 & scale)
	{
		this->scale = scale;
		UpdateTransformation();
	}

	void SetRotation(const glm::vec2 & pos)
	{
		this->rotation = rotation;
		UpdateTransformation();
	}

	glm::vec2 GetPosition()
	{
		return this->position;
	}

	glm::mat4 GetTransformationMat()
	{
		return this->transformationMat;
	}
};
