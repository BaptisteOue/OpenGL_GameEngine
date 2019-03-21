#pragma once

#include "Mesh.h"
#include "../materials/Material.h"
#include <glm/glm.hpp>

class GameObject
{
private:
	Mesh m_Mesh;
	Material m_Material;

	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	float m_Scale;

	float m_TessLevelOuter;
	float m_TessLevelInner;

public:
	GameObject(const GameObject& gameObject);
	GameObject(const Mesh& mesh, Material& material, glm::vec3 position = glm::vec3(0), glm::vec3 rotation = glm::vec3(0), float scale = 1);
	~GameObject();

	Material& GetMaterial();
	Mesh& GetMesh();
	const glm::vec3 GetPosition() const;
	const glm::vec3 GetRotation() const;
	const float GetScale() const;
	const float GetTessLevelOuter() const;
	const float GetTessLevelInner() const;

	void SetPosition(const glm::vec3& position);
	void SetRotation(const glm::vec3& rotation);
	void SetScale(const float scale);

	void SetTessLevelOuter(float value);
	void SetTessLevelInner(float value);

	void Draw();
	void CleanUp();
};