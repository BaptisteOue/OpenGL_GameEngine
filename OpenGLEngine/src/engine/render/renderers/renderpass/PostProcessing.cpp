#include "PostProcessing.h"


PostProcessing::PostProcessing()
	: m_PPShader{},
	m_QuadVAO{0}
{
}

PostProcessing::~PostProcessing()
{
}

void PostProcessing::Create()
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
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (const void*) (sizeof(float) * 2));
	glBindVertexArray(0);

	// Create shader
	m_PPShader.CreateShaderProgram();
}

void PostProcessing::ExecuteRenderPass(LightingPassOutput lightingPassOutput)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_PPShader.Use(true);
	glBindVertexArray(m_QuadVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, lightingPassOutput.outputFramebuffer.GetColorTexture());
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
	m_PPShader.Use(false);
}

void PostProcessing::CleanUp()
{
	m_PPShader.CleanUp();
}
