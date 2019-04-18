#pragma once

#include <glm/glm.hpp>
#include "../models/GameObject.h"

class BasicLight
{
protected :
	glm::vec3 m_Color;
	float m_Intensity;
	bool m_CastShadow;

public:
	BasicLight(const glm::vec3& color = glm::vec3(1), float intensity = 0.1f, bool castShadow = false);
	~BasicLight();

	const glm::vec3 GetColor() const;
	const float GetIntensity() const;
	const bool IsCastingShadow() const;
	virtual void SetColor(const glm::vec3& color);
	void SetIntensity(float intensity);
	void SetCastShadow(bool value);
};