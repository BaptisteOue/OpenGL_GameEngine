#include "HDRGammaPass.h"
#include "../../core/Window.h"

HDRGammaCorrectionPass::HDRGammaCorrectionPass()
	: m_HDRGammaShader{},
	m_QuadVAO{0}
{
}

HDRGammaCorrectionPass::~HDRGammaCorrectionPass()
{
}

void HDRGammaCorrectionPass::Create()
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
	m_HDRGammaShader.CreateShaderProgram();
}

void HDRGammaCorrectionPass::ExecuteRenderPass(LightingPassOutput lightingPassOutput)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_HDRGammaShader.Use(true);
	m_HDRGammaShader.LoadGammaUniform(Window::s_Gamma);

	glBindVertexArray(m_QuadVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, lightingPassOutput.outputFramebuffer.GetColorTexture());
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
	m_HDRGammaShader.Use(false);
}

void HDRGammaCorrectionPass::CleanUp()
{
	m_HDRGammaShader.CleanUp();
}
