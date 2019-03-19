#include "Material.h"

#pragma region Public API

Material::Material(glm::vec3&& Ka, glm::vec3&& Kd, glm::vec3&& Ks, float reflectivity, float shineDamper)
	: m_Ka(Ka),
	m_Kd(Kd),
	m_Ks(Ks),
	m_Reflectivity(reflectivity),
	m_ShineDamper(shineDamper),
	m_texture(nullptr)
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
	m_texture = new Texture(texture);
}

const Texture Material::GetTexture() const
{
	return *m_texture;
}

bool Material::IsTextured() const
{
	return m_texture != nullptr;
}

void Material::CleanUp()
{
	if (m_texture != nullptr)
		delete m_texture;
}

#pragma endregion