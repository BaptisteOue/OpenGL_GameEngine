#pragma once

#include "BasicLight.h"
#include <glm/glm.hpp>

class PointLight : public BasicLight
{
protected:
	glm::vec3 m_Position;

	float m_ConstAtt;
	float m_LinearAtt;
	float m_QuadraticAtt;
	
public:
	PointLight(const glm::vec3& color, const glm::vec3& position);
	~PointLight();

	const glm::vec3 GetPosition() const;
	const float GetConstAtt() const;
	const float GetLinearAtt() const;
	const float GetQuadraticAtt() const;

	void SetPosition(const glm::vec3& position);
	void SetAttenuation(const float constant, const float linear, const float quadratic);
};