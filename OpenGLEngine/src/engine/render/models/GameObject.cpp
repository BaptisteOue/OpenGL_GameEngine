#include "GameObject.h"
#include <iostream>

#pragma region Public API

GameObject::GameObject(const Mesh& mesh, Material& material, const glm::vec3& position, const glm::vec3& rotation, float scale)
	: m_Mesh(mesh),
	m_Material(material),
	m_Position(position),
	m_Rotation(rotation),
	m_Scale(scale),
	m_TessLevelInner(1),
	m_TessLevelOuter(1)
{
	if (material.IsTextured() && !mesh.HasTextureCoords())
	{
		std::cout << "Model doesn't have uvs coordinates. Remove texture flag from material";
		material.SetTexturedFlag(false);
		material.RemoveTexture();
	}
}

GameObject::GameObject(const GameObject & gameObject)
	: m_Mesh(gameObject.m_Mesh),
	m_Material(gameObject.m_Material),
	m_Position(gameObject.m_Position),
	m_Rotation(gameObject.m_Rotation),
	m_Scale(gameObject.m_Scale),
	m_TessLevelInner(gameObject.m_TessLevelInner),
	m_TessLevelOuter(gameObject.m_TessLevelOuter)
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

const glm::vec3 GameObject::GetScale() const
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

void GameObject::SetScale(const glm::vec3& scale)
{
	m_Scale = scale;
}

void GameObject::SetTessLevelOuter(float value)
{
	if (m_TessLevelOuter = value; m_TessLevelOuter < 1)
		m_TessLevelOuter = 1;

	std::cout << "Outer tesselation level : " << m_TessLevelOuter << std::endl;
}

void GameObject::SetTessLevelInner(float value)
{
	if (m_TessLevelInner = value; m_TessLevelInner < 1)
		m_TessLevelInner = 1;

	std::cout << "Inner tesselation level : " << m_TessLevelInner << std::endl;
}

void GameObject::Draw()
{
	m_Mesh.Draw();
}

void GameObject::DrawTesselated()
{
	m_Mesh.DrawTesselated();
}

void GameObject::CleanUp()
{
	m_Mesh.CleanUp();
	m_Material.CleanUp();
}

#pragma endregion



