#include "BasicLight.h"
#include "../utils/Loader.h"

#pragma region Public API

BasicLight::BasicLight(const glm::vec3& color, float intensity, bool castShadow)
	: m_Color(color),
	m_Intensity(intensity),
	m_CastShadow(castShadow)
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

const bool BasicLight::IsCastingShadow() const
{
	return m_CastShadow;
}

void BasicLight::SetColor(const glm::vec3& color)
{
	m_Color = color;
}

void BasicLight::SetIntensity(float intensity)
{
	m_Intensity = intensity;
}

void BasicLight::SetCastShadow(bool value)
{
	m_CastShadow = value;
}

#pragma endregion
