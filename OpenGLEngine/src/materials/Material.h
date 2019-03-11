#pragma once

#include <glm/glm.hpp>

class Material
{
private:
	glm::vec3 m_Ka;
	glm::vec3 m_Kd;
	glm::vec3 m_Ks;
	float m_Reflectivity;
	float m_ShineDamper;
public:
	Material(glm::vec3&& Ka, glm::vec3&& Kd, glm::vec3&& Ks, float reflectivity, float shineDamper);
	~Material();

	const glm::vec3 GetKa() const;
	const glm::vec3 GetKd() const;
	const glm::vec3 GetKs() const;
	const float GetReflectivity() const;
	const float GetShineDamper() const;
};