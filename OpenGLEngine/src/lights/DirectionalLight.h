#pragma once

#include <glm/glm.hpp>
#include "BasicLight.h"


class DirectionalLight : public BasicLight
{
private:
	glm::vec4 m_Direction;
public:
	DirectionalLight(glm::vec4&& color, glm::vec4&& direction);
	~DirectionalLight();

	const glm::vec4 GetDirection() const;
};