#pragma once

#include "BasicLight.h"
#include <glm/glm.hpp>


class DirectionalLight : public BasicLight
{
private:
	glm::vec3 m_Direction;
	glm::vec3 m_FakePosition;
public:
	DirectionalLight();
	DirectionalLight(const glm::vec3& color, const glm::vec3& direction, float intensity = 1, bool castShadow = true);
	~DirectionalLight();

	const glm::vec3 GetDirection() const;
	const glm::vec3 GetFakePosition() const;
	glm::vec3 GetDirection();

	void SetDirection(const glm::vec3& direction);
};