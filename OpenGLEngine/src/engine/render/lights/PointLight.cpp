#include "PointLight.h"
#include "../utils/Loader.h"
#include <iostream>


#pragma region Public API

PointLight::PointLight(const PointLight & pointLight)
	: BasicLight{ pointLight.m_Color, pointLight.m_Intensity, pointLight.m_CastShadow },
	m_Position{ pointLight.m_Position },
	m_ConstAtt{ pointLight.m_ConstAtt },
	m_LinearAtt{ pointLight.m_LinearAtt },
	m_QuadraticAtt{ pointLight.m_QuadraticAtt }
{
}

PointLight::PointLight(const glm::vec3& color, const glm::vec3& position, float intensity, bool castShadow)
	: BasicLight(color, intensity, castShadow),
	m_Position(position),
	m_QuadraticAtt(0.05f),
	m_LinearAtt(0.2f),
	m_ConstAtt(1.0f)
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

void PointLight::SetColor(const glm::vec3 & color)
{
	BasicLight::SetColor(color);
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

