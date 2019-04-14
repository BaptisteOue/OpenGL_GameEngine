#include "DirectionalLight.h"

#pragma region Public API

DirectionalLight::DirectionalLight()
	: BasicLight(),
	m_Direction{ glm::vec3(-1, -1, -1) },
	m_FakePosition { m_Direction }
{
	m_FakePosition *= -100;
}

DirectionalLight::DirectionalLight(const glm::vec3& color, const glm::vec3& direction, float intensity, bool castShadow)
	: BasicLight(color, intensity, castShadow),
	m_Direction(direction),
	m_FakePosition(direction)
{
	m_FakePosition *= -100;
}

DirectionalLight::~DirectionalLight()
{
}

const glm::vec3 DirectionalLight::GetDirection() const
{
	return m_Direction;
}

const glm::vec3 DirectionalLight::GetFakePosition() const
{
	return m_FakePosition;
}

glm::vec3 DirectionalLight::GetDirection()
{
	return m_Direction;
}

void DirectionalLight::SetDirection(const glm::vec3& direction)
{
	m_Direction = direction;
	m_FakePosition = direction;
	m_FakePosition *= -100;
}

#pragma endregion