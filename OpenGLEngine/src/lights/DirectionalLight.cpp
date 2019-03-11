#include "DirectionalLight.h"
#include <glm/glm.hpp>

DirectionalLight::DirectionalLight(glm::vec3&& color, glm::vec3&& direction)
	: BasicLight(color), m_Direction(direction)
{
}

DirectionalLight::~DirectionalLight()
{
}

const glm::vec3 DirectionalLight::GetDirection() const
{
	return m_Direction;
}
