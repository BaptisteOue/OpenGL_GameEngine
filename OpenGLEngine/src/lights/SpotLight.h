#pragma once

#include "PointLight.h"
#include <glm/glm.hpp>

class SpotLight : public PointLight
{
private:
	float m_CutoffAngle;
	glm::vec3 m_Direction;

public:
	SpotLight(PointLight pointLight, float cutoffAngle, const glm::vec3& direction);
	~SpotLight();

	const float GetCutoffAngle() const;
	const glm::vec3 GetDirection() const;

	void SetCutoffAngle(const float cutoffAngle);
	void SetDirection(const glm::vec3& direction);

};