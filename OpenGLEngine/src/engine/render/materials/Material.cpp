#include "Material.h"

#pragma region Public API

Material::Material(const Material& material)
	: m_Ka(material.m_Ka),
	m_Kd(material.m_Kd),
	m_Ks(material.m_Ks),
	m_Reflectivity(material.m_Reflectivity),
	m_ShineDamper(material.m_ShineDamper),
	m_Texture(nullptr)
{
	if(material.IsTextured())
		m_Texture = new Texture(*material.m_Texture);
}

Material::Material(glm::vec3&& Ka, glm::vec3&& Kd, glm::vec3&& Ks, float reflectivity, float shineDamper)
	: m_Ka(Ka),
	m_Kd(Kd),
	m_Ks(Ks),
	m_Reflectivity(reflectivity),
	m_ShineDamper(shineDamper),
	m_Texture(nullptr)
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

void Material::AddTexture(const Texture& texture)
{
	m_Texture = new Texture(texture);
}

const Texture Material::GetTexture() const
{
	return *m_Texture;
}

bool Material::IsTextured() const
{
	return m_Texture != nullptr;
}

void Material::CleanUp()
{
	if (m_Texture != nullptr)
		delete m_Texture;
}

#pragma endregion