#include "ParticuleGroup.h"
#include <GL/glew.h>
#include <vector>
#include <iostream>

#pragma region Public API

ParticuleGroup::ParticuleGroup()
	: m_VaoIDs{0},
	m_VertexCount(0)
{
}

ParticuleGroup::~ParticuleGroup()
{
}

void ParticuleGroup::LoadParticuleGroup(const std::vector<GLfloat>& positions, const std::vector<GLfloat>& speeds, const std::vector<GLfloat>& startTimes)
{
	/* Generate vo, vbo and ebo */
	glGenVertexArrays(1, m_VaoIDs);

	/* Configure attributes */
	glBindVertexArray(m_VaoIDs[0]);

	AddData(0, 3, positions);
	AddData(1, 3, speeds);
	AddData(2, 1, startTimes);

	glBindVertexArray(0);
}

void ParticuleGroup::CleanUp()
{
	glDeleteBuffers((GLsizei)m_Vbos.size(), m_Vbos.data());
}

void ParticuleGroup::SetNbParticules(int nbParticules)
{
	m_NbParticules = nbParticules;
}

void ParticuleGroup::Draw() const
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPointSize(10.0f);
	glBindVertexArray(m_VaoIDs[0]);
	glDrawArrays(GL_POINTS, 0, m_NbParticules);
	glBindVertexArray(0);
	glDisable(GL_BLEND);
}


#pragma endregion


#pragma region Private API

void ParticuleGroup::AddData(const int attribIndex, const int count, const std::vector<GLfloat>& data)
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
#pragma endregion