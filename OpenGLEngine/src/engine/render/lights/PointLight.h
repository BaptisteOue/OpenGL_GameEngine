#pragma once

#include "BasicLight.h"
#include <glm/glm.hpp>
#include "../models/GameObject.h"

class PointLight : public BasicLight
{
protected:
	glm::vec3 m_Position;

	float m_ConstAtt;
	float m_LinearAtt;
	float m_QuadraticAtt;

	GameObject* m_LightObject;
	
public:
	PointLight(const PointLight& pointLight);
	PointLight(const glm::vec3& color, const glm::vec3& position, float intensity = 1, bool castShadow = false);
	~PointLight();

	const glm::vec3 GetPosition() const;
	const float GetConstAtt() const;
	const float GetLinearAtt() const;
	const float GetQuadraticAtt() const;

	const GameObject& GetLightObject() const;
	GameObject& GetLightObject();

	void SetPosition(const glm::vec3& position);
	void SetColor(const glm::vec3& color) override;
	void SetAttenuation(const float constant, const float linear, const float quadratic);
};