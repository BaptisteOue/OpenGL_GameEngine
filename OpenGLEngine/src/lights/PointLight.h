#pragma once

#include <glm/glm.hpp>
#include "BasicLight.h"

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
	void SetPosition(const glm::vec3& position);

	void SetAttenuation(const float constant, const float linear, const float quadratic);
	float GetConstAtt() const;
	float GetLinearAtt() const;
	float GetQuadraticAtt() const;
};