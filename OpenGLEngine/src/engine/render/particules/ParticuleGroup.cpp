#include "ParticuleGroup.h"
#include <GL/glew.h>
#include <vector>
#include <iostream>

#pragma region Public API

ParticuleGroup::ParticuleGroup()
	: m_VaoPingPong{0},
	m_VertexCount(0)
{
}

ParticuleGroup::~ParticuleGroup()
{
}

void ParticuleGroup::LoadParticuleGroup(const std::vector<GLfloat>& positions, const std::vector<GLfloat>& initialVelocity, const std::vector<GLfloat>& startTimes)
{
	glGenVertexArrays(2, m_VaoPingPong);

	/* Configure attributes */
	glBindVertexArray(m_VaoPingPong[m_DrawBuffer]);
	AddData(0, 3, positions);
	AddData(1, 1, startTimes);
	AddData(2, 3, initialVelocity);
	AddData(3, 3, initialVelocity);

	glBindVertexArray(m_VaoPingPong[1 - m_DrawBuffer]);
	AddData(0, 3, positions);
	AddData(1, 1, startTimes);
	AddData(2, 3, initialVelocity);
	AddData(3, 3, initialVelocity);

	glBindVertexArray(0);

	glGenTransformFeedbacks(2, m_FeedbackIDs);

	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, m_FeedbackIDs[m_DrawBuffer]);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, m_Vbos[0]);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 1, m_Vbos[1]);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 2, m_Vbos[2]);

	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, m_FeedbackIDs[1 - m_DrawBuffer]);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, m_Vbos[4]);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 1, m_Vbos[5]);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 2, m_Vbos[6]);

}

void ParticuleGroup::CleanUp()
{
	glDeleteBuffers((GLsizei)m_Vbos.size(), m_Vbos.data());
}

void ParticuleGroup::SetNbParticules(int nbParticules)
{
	m_NbParticules = nbParticules;
}


void ParticuleGroup::UpdatePass()
{
	glEnable(GL_RASTERIZER_DISCARD);

	// Specify the buffer that will receive the data
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, m_FeedbackIDs[m_DrawBuffer]);
	
	glBeginTransformFeedback(GL_POINTS);

	glBindVertexArray(m_VaoPingPong[1 - m_DrawBuffer]);
	glDrawArrays(GL_POINTS, 0, m_NbParticules);
	glBindVertexArray(0);

	glEndTransformFeedback();

	glDisable(GL_RASTERIZER_DISCARD);

}

void ParticuleGroup::RenderPass()
{
	glEnable(GL_PROGRAM_POINT_SIZE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindVertexArray(m_VaoPingPong[m_DrawBuffer]);
	glDrawTransformFeedback(GL_POINTS, m_FeedbackIDs[m_DrawBuffer]);
	glDisable(GL_BLEND);
	glDisable(GL_PROGRAM_POINT_SIZE);

	// Swap buffers
	m_DrawBuffer = 1 - m_DrawBuffer;
}

#pragma endregion


#pragma region Private API

void ParticuleGroup::AddData(const int attribIndex, const int count, const std::vector<GLfloat>& data)
{
	GLuint vboID = 0;
	glGenBuffers(1, &vboID);

	/* Fill vbo */
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), data.data(), GL_STREAM_DRAW);

	/* Configure attributes */
	glEnableVertexAttribArray(attribIndex);
	glVertexAttribPointer(attribIndex, count, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	m_Vbos.emplace_back(vboID);
}




#pragma endregion