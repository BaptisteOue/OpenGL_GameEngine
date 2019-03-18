#pragma once

#include <glm/glm.hpp>
#include "PointLight.h"

class SpotLight : public PointLight
{
private:
	float m_CutoffAngle;
	glm::vec3 m_Direction;

public:
	SpotLight(PointLight pointLight, float cutoffAngle, const glm::vec3& direction);

	~SpotLight();

	float GetCutoffAngle() const;
	glm::vec3 GetDirection() const;

	void SetCutoffAngle(const float cutoffAngle);
	void SetDirection(const glm::vec3& direction);

};