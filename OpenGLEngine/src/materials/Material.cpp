#include "Material.h"

Material::Material(glm::vec3&& Ka, glm::vec3&& Kd, glm::vec3&& Ks, float reflectivity, float shineDamper)
	: m_Ka(Ka), m_Kd(Kd), m_Ks(Ks), m_Reflectivity(reflectivity), m_ShineDamper(shineDamper)
{
}

Material::~Material()
{
}

const glm::vec3 Material::GetKa() const
{
	return m_Ka;
}

const glm::vec3 Material::GetKd() const
{
	return m_Kd;
}

const glm::vec3 Material::GetKs() const
{
	return m_Ks;
}

const float Material::GetReflectivity() const
{
	return m_Reflectivity;
}

const float Material::GetShineDamper() const
{
	return m_ShineDamper;
}

