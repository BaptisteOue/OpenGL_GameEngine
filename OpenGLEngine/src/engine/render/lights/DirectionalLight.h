#pragma once

#include "BasicLight.h"
#include <glm/glm.hpp>


class DirectionalLight : public BasicLight
{
private:
	glm::vec3 m_Direction;
public:
	DirectionalLight(const glm::vec3& color, const glm::vec3& direction);
	~DirectionalLight();

	const glm::vec3 GetDirection() const;
};