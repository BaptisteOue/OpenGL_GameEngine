#pragma once

#include "BasicLight.h"
#include <glm/glm.hpp>


class DirectionalLight : public BasicLight
{
private:
	glm::vec3 m_Direction;
public:
	DirectionalLight(const glm::vec3& color, const glm::vec3& direction, float intensity = 1);
	~DirectionalLight();

	const glm::vec3 GetDirection() const;
	glm::vec3 GetDirection();

	void SetDirection(const glm::vec3& direction);
};