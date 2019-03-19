#include "BasicLight.h"

#pragma region Public API

BasicLight::BasicLight(const glm::vec3& color)
	: m_Color(color)
{
}


BasicLight::~BasicLight()
{
}

const glm::vec3 BasicLight::GetColor() const
{
	return m_Color;
}

void BasicLight::SetColor(const glm::vec3& color)
{
	m_Color = color;
}

#pragma endregion
