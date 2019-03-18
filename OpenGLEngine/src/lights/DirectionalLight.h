#pragma once

#include <glm/glm.hpp>
#include "BasicLight.h"


class DirectionalLight : public BasicLight
{
private:
	glm::vec3 m_Direction;
public:
	DirectionalLight(const glm::vec3& color, const glm::vec3& direction);
	~DirectionalLight();

	const glm::vec3 GetDirection() const;
};