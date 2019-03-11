#include <GL/glew.h>
#include "Mesh.h"
#include <vector>

#pragma region Public API

Mesh::Mesh()
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
    glBindVertexArray(m_VaoID);
    glDrawElements(GL_TRIANGLES, m_VertexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}


void Mesh::CleanUp()
{
	glDeleteBuffers(m_Vbos.size(), m_Vbos.data());
	glDeleteBuffers(1, &m_EboID);
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