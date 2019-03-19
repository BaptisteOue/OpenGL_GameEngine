#pragma once

#include <glm/glm.hpp>
#include "Texture.h"

class Material
{
private:
	glm::vec3 m_Ka;
	glm::vec3 m_Kd;
	glm::vec3 m_Ks;
	float m_Reflectivity;
	float m_ShineDamper;

	Texture* m_texture;

public:
	Material(glm::vec3&& Ka, glm::vec3&& Kd, glm::vec3&& Ks, float reflectivity, float shineDamper);
	~Material();

	const glm::vec3 GetKa() const;
	const glm::vec3 GetKd() const;
	const glm::vec3 GetKs() const;
	const float GetReflectivity() const;
	const float GetShineDamper() const;

	void AddTexture(const Texture& texture);
	const Texture GetTexture() const;

	bool IsTextured() const;

	void CleanUp();
};