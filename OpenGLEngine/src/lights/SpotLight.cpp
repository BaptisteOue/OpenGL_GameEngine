#include "SpotLight.h"
#include <glm/glm.hpp>

SpotLight::SpotLight(PointLight pointLight, float cutoffAngle, const glm::vec3& direction)
	: PointLight(pointLight), m_Direction(direction)
{
	SetCutoffAngle(cutoffAngle);
}

SpotLight::~SpotLight()
{
}

float SpotLight::GetCutoffAngle() const
{
	return m_CutoffAngle;
}

glm::vec3 SpotLight::GetDirection() const
{
	return m_Direction;
}

void SpotLight::SetCutoffAngle(const float cutoffAngle)
{
	m_CutoffAngle = glm::cos(glm::radians(cutoffAngle));
}

void SpotLight::SetDirection(const glm::vec3& direction)
{
	m_Direction = direction;
}
