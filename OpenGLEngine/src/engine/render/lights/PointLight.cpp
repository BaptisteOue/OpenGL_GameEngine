#include "PointLight.h"
#include "../utils/Loader.h"
#include <iostream>


#pragma region Public API

PointLight::PointLight(const PointLight & pointLight)
	: BasicLight(pointLight.m_Color, pointLight.m_Intensity, pointLight.m_CastShadow),
	m_Position(pointLight.m_Position),
	m_ConstAtt(pointLight.m_ConstAtt),
	m_LinearAtt(pointLight.m_LinearAtt),
	m_QuadraticAtt(pointLight.m_QuadraticAtt)
{
	m_LightObject = new GameObject(pointLight.GetLightObject());
}

PointLight::PointLight(const glm::vec3& color, const glm::vec3& position, float intensity, bool castShadow)
	: BasicLight(color, intensity, castShadow),
	m_Position(position),
	m_QuadraticAtt(0.0f),
	m_LinearAtt(0.0f),
	m_ConstAtt(1.0f)
{
	Mesh m(Loader::LoadOBJ("./res/sphere.obj"));
	Material material(glm::vec3(color), glm::vec3(color), glm::vec3(color), 0, 1);
	m_LightObject = new GameObject(m, material, position, glm::vec3(0), 1.0f);
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
	m_LightObject->SetPosition(position);
}

void PointLight::SetColor(const glm::vec3 & color)
{
	BasicLight::SetColor(color);
	m_LightObject->GetMaterial().SetKa(color);
	m_LightObject->GetMaterial().SetKd(color);
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

const GameObject & PointLight::GetLightObject() const
{
	return *m_LightObject;
}

GameObject & PointLight::GetLightObject()
{
	return *m_LightObject;
}
#pragma endregion

