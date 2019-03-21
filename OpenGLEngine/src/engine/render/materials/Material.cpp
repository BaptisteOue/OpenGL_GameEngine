#include "Material.h"

#pragma region Public API

Material::Material(const Material& material)
	: m_Ka(material.m_Ka),
	m_Kd(material.m_Kd),
	m_Ks(material.m_Ks),
	m_Reflectivity(material.m_Reflectivity),
	m_ShineDamper(material.m_ShineDamper),
	m_IsTextured(material.m_IsTextured),
	m_Texture(nullptr)
{
	if (m_IsTextured)
		m_Texture = new Texture(material.m_Texture->GetTextureID(), material.m_Texture->GetActiveTexture());
}

Material::Material(glm::vec3&& Ka, glm::vec3&& Kd, glm::vec3&& Ks, float reflectivity, float shineDamper)
	: m_Ka(Ka),
	m_Kd(Kd),
	m_Ks(Ks),
	m_Reflectivity(reflectivity),
	m_ShineDamper(shineDamper),
	m_IsTextured(false),
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

void Material::SetKa(const glm::vec3 & Ka)
{
	m_Ka = Ka;
}

void Material::SetKd(const glm::vec3 & Kd)
{
	m_Kd = Kd;
}

void Material::SetKs(const glm::vec3 & Ks)
{
	m_Ks = Ks;
}

void Material::SetReflectivity(float reflectivity)
{
	m_Reflectivity = reflectivity;
}

void Material::SetShineDamper(float shineDamper)
{
	m_ShineDamper = shineDamper;
}

void Material::AddTexture(const Texture& texture)
{
	m_Texture = new Texture(texture);
	m_IsTextured = true;
}

void Material::RemoveTexture()
{
	CleanUp();
}

const Texture Material::GetTexture() const
{
	return *m_Texture;
}

bool Material::IsTextured() const
{
	return m_IsTextured;
}

void Material::SetTexturedFlag(bool value)
{
	m_IsTextured = value;
}

void Material::CleanUp()
{
	if (m_Texture != nullptr)
		delete m_Texture;
}

#pragma endregion