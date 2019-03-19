#include "PointLight.h"


#pragma region Public API

PointLight::PointLight(const glm::vec3& color, const glm::vec3& position, float intensity)
	: BasicLight(color, intensity), m_Position(position)
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

const float PointLight::GetConstAtt() const
{
	return m_ConstAtt;
}

const float PointLight::GetLinearAtt() const
{
	return m_LinearAtt;
}

const float PointLight::GetQuadraticAtt() const
{
	return m_QuadraticAtt;
}

#pragma endregion

