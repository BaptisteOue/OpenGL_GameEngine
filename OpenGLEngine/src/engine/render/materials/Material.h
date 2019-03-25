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

	bool m_IsTextured;

	Texture* m_Texture;

public:
	Material(const Material& material);
	Material(const glm::vec3& Ka, const glm::vec3& Kd, const glm::vec3& Ks, float reflectivity, float shineDamper);
	~Material();

	const glm::vec3 GetKa() const;
	const glm::vec3 GetKd() const;
	const glm::vec3 GetKs() const;
	const float GetReflectivity() const;
	const float GetShineDamper() const;

	void SetKa(const glm::vec3& Ka);
	void SetKd(const glm::vec3& Kd);
	void SetKs(const glm::vec3& Ks);
	void SetReflectivity(float reflectivity);
	void SetShineDamper(float shineDamper);


	void AddTexture(const Texture& texture);
	void RemoveTexture();

	const Texture GetTexture() const;

	bool IsTextured() const;
	void SetTexturedFlag(bool value);

	void CleanUp();
};