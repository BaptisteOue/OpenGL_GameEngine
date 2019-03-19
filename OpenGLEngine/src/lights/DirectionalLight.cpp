#include "DirectionalLight.h"

#pragma region Public API

DirectionalLight::DirectionalLight(const glm::vec3& color, const glm::vec3& direction)
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

#pragma endregion