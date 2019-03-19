#include "GameObject.h"
#include <iostream>

#pragma region Public API

GameObject::GameObject(const Mesh& mesh, const Material& material, glm::vec3 position, glm::vec3 rotation, float scale)
	: m_Mesh(mesh),
	m_Material(material),
	m_Position(position),
	m_Rotation(rotation),
	m_Scale(scale),
	m_TessLevelInner(1),
	m_TessLevelOuter(1)
{
}

GameObject::~GameObject()
{
}

Material& GameObject::GetMaterial()
{
	return m_Material;
}

Mesh& GameObject::GetMesh()
{
	return m_Mesh;
}

const glm::vec3 GameObject::GetPosition() const
{
	return m_Position;
}

const glm::vec3 GameObject::GetRotation() const
{
	return m_Rotation;
}

const float GameObject::GetScale() const
{
	return m_Scale;
}

const float GameObject::GetTessLevelOuter() const
{
	return m_TessLevelOuter;
}

const float GameObject::GetTessLevelInner() const
{
	return m_TessLevelInner;
}

void GameObject::SetPosition(const glm::vec3 & position)
{
	m_Position = position;
}

void GameObject::SetRotation(const glm::vec3 & rotation)
{
	m_Rotation = rotation;
}

void GameObject::SetScale(const float scale)
{
	m_Scale = scale;
}

void GameObject::SetTessLevelOuter(float value)
{
	m_TessLevelOuter = value;
	if (m_TessLevelOuter < 1)
		m_TessLevelOuter = 1;

	std::cout << "Outer tesselation level : " << m_TessLevelOuter << std::endl;
}

void GameObject::SetTessLevelInner(float value)
{
	m_TessLevelInner = value;
	if (m_TessLevelInner < 1)
		m_TessLevelInner = 1;

	std::cout << "Inner tesselation level : " << m_TessLevelInner << std::endl;
}

void GameObject::Draw()
{
	m_Mesh.Draw();
}

void GameObject::CleanUp()
{
	m_Mesh.CleanUp();
	m_Material.CleanUp();
}

#pragma endregion



