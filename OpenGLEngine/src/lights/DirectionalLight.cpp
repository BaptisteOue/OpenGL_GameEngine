#include "DirectionalLight.h"
#include <glm/glm.hpp>

DirectionalLight::DirectionalLight(glm::vec4&& color, glm::vec4&& direction)
	: BasicLight(color), m_Direction(direction)
{
}

DirectionalLight::~DirectionalLight()
{
}

const glm::vec4 DirectionalLight::GetDirection() const
{
	return m_Direction;
}
