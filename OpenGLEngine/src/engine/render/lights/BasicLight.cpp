#include "BasicLight.h"

#pragma region Public API

BasicLight::BasicLight(const glm::vec3& color, float intensity)
	: m_Color(color),
	m_Intensity(intensity)
{
}


BasicLight::~BasicLight()
{
}

const glm::vec3 BasicLight::GetColor() const
{
	return m_Color;
}

const float BasicLight::GetIntensity() const
{
	return m_Intensity;
}

void BasicLight::SetColor(const glm::vec3& color)
{
	m_Color = color;
}

void BasicLight::SetIntensity(float intensity)
{
	m_Intensity = intensity;
}

#pragma endregion
