#include "QuadRenderer.h"

QuadRenderer::QuadRenderer()
	: m_QuadVAO{0}
{
}

QuadRenderer::~QuadRenderer()
{
}

void QuadRenderer::Init()
{
	// Create a VAO for a 2D quad
	glGenVertexArrays(1, &m_QuadVAO);
	GLuint vbo;
	glGenBuffers(1, &vbo);

	glBindVertexArray(m_QuadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_Vertices), m_Vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (const void*)(sizeof(float) * 2));
	glBindVertexArray(0);
}

void QuadRenderer::Render()
{
	glBindVertexArray(m_QuadVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
	
}


