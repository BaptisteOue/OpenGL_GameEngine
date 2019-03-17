#include "Mesh.h"
#include <GL/glew.h>
#include <vector>
#include <iostream>

#pragma region Public API

Mesh::Mesh()
	: m_VaoID(0), m_VertexCount(0), m_TessLevelInner(1), m_TessLevelOuter(1)
{
}

Mesh::~Mesh()
{
}

void Mesh::LoadMesh(std::vector<GLfloat>& positions, std::vector<GLfloat>& normals, std::vector<GLuint>& indices)
{
	m_VertexCount = indices.size();

	/* Generate vo, vbo and ebo */
	glGenVertexArrays(1, &m_VaoID);

	/* Configure attributes */
	glBindVertexArray(m_VaoID);

	AddData(0, 3, positions);
	AddData(1, 3, normals);

	AddIndices(indices);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::Draw()
{
	glEnable(GL_CULL_FACE);
    glBindVertexArray(m_VaoID);
	glPatchParameteri(GL_PATCH_VERTICES, 3);
    glDrawElements(GL_PATCHES, m_VertexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
	glDisable(GL_CULL_FACE);
}

void Mesh::CleanUp()
{
	glDeleteBuffers(m_Vbos.size(), m_Vbos.data());
	glDeleteBuffers(1, &m_EboID);

}

float Mesh::GetTessLevelOuter() const
{
	return m_TessLevelOuter;
}

float Mesh::GetTessLevelInner() const
{
	return m_TessLevelInner;
}

void Mesh::SetTessLevelOuter(float value)
{
	m_TessLevelOuter = value;
	if (m_TessLevelOuter < 1)
		m_TessLevelOuter = 1;

	std::cout << "Outer tesselation level : " << m_TessLevelOuter << std::endl;
}

void Mesh::SetTessLevelInner(float value)
{
	m_TessLevelInner = value;
	if (m_TessLevelInner < 1)
		m_TessLevelInner = 1;

	std::cout << "Inner tesselation level : " << m_TessLevelInner << std::endl;
}


#pragma endregion


#pragma region Private API

void Mesh::AddData(int attribIndex, int count, std::vector<GLfloat>data)
{
	GLuint vboID = 0;
	glGenBuffers(1, &vboID);

	/* Fill vbo */
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), data.data(), GL_STATIC_DRAW);

	/* Configure attributes */
	glEnableVertexAttribArray(attribIndex);
	glVertexAttribPointer(attribIndex, count, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	m_Vbos.emplace_back(vboID);
}

void Mesh::AddIndices(std::vector<GLuint>indices)
{
	GLuint eboId = 0;
	glGenBuffers(1, &eboId);

	/* Fill ebo */
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

#pragma endregion