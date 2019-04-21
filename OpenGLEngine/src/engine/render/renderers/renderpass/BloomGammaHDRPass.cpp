#include "BloomGammaHDRPass.h"
#include "../../core/Window.h"

BloomGammaHDRPass::BloomGammaHDRPass()
	: m_BloomGammaHDRShader{}
{
}

BloomGammaHDRPass::~BloomGammaHDRPass()
{
}

void BloomGammaHDRPass::Create()
{
	m_QuadRenderer.Init();

	// Create shader
	m_BloomGammaHDRShader.CreateShaderProgram();
}

void BloomGammaHDRPass::ExecuteRenderPass(LightingPassOutput lightingPassOutput, BlurPassOutput blurPassOutput)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_BloomGammaHDRShader.Use(true);
	m_BloomGammaHDRShader.LoadGammaUniform(Window::s_Gamma);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, lightingPassOutput.outputFramebuffer.GetColorTexture(0));

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, blurPassOutput.outputFramebuffer.GetColorTexture(0));

	m_QuadRenderer.Render();

	m_BloomGammaHDRShader.Use(false);
}

void BloomGammaHDRPass::CleanUp()
{
	m_BloomGammaHDRShader.CleanUp();
}
