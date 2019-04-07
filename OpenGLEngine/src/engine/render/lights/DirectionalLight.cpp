#include "DirectionalLight.h"

#pragma region Public API

DirectionalLight::DirectionalLight(const glm::vec3& color, const glm::vec3& direction, float intensity)
	: BasicLight(color, intensity), m_Direction(direction)
{
}

DirectionalLight::~DirectionalLight()
{
}

const glm::vec3 DirectionalLight::GetDirection() const
{
	return m_Direction;
}

glm::vec3 DirectionalLight::GetDirection()
{
	return m_Direction;
}


#pragma endregion