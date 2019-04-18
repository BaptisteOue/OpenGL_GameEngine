#include "SpotLight.h"
#include <glm/glm.hpp>
#include "../utils/Loader.h"

#pragma region Public API

SpotLight::SpotLight(PointLight pointLight, float cutoffAngle, const glm::vec3& direction)
	: PointLight(pointLight), m_Direction(direction)
{
	SetCutoffAngle(cutoffAngle);
}

SpotLight::~SpotLight()
{
}

const float SpotLight::GetCutoffAngle() const
{
	return m_CutoffAngle;
}

const glm::vec3 SpotLight::GetDirection() const
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

void SpotLight::SimulateTorch(Camera & camera)
{
	m_Position = camera.GetPos();
	m_Direction = camera.GetFront();
}

#pragma endregion


