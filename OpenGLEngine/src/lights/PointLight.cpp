#include "PointLight.h"


#pragma region Public API

PointLight::PointLight(const glm::vec3& color, const glm::vec3& position)
	: BasicLight(color), m_Position(position)
{
}

PointLight::~PointLight()
{
}

const glm::vec3 PointLight::GetPosition() const
{
	return m_Position;
}

void PointLight::SetPosition(const glm::vec3& position)
{
	m_Position = position;
}

void PointLight::SetAttenuation(float constant, float linear, float quadratic)
{
	m_ConstAtt = constant;
	m_LinearAtt = linear;
	m_QuadraticAtt = quadratic;
}

float PointLight::GetConstAtt() const
{
	return m_ConstAtt;
}

float PointLight::GetLinearAtt() const
{
	return m_LinearAtt;
}

float PointLight::GetQuadraticAtt() const
{
	return m_QuadraticAtt;
}

#pragma endregion

