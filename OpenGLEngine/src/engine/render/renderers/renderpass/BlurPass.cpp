#include "BlurPass.h"
#include <iostream>

BlurPass::BlurPass()
	: m_BlurShader{},
	m_PingPongFBOs{FrameBuffer{1080, 720}, FrameBuffer{1080, 720}},
	m_QuadRenderer{}
{
}

BlurPass::~BlurPass()
{
}

void BlurPass::Create()
{
	for (int i = 0; i < 2; i++)
	{
		m_PingPongFBOs[i].Init();
		m_PingPongFBOs[i].AddTexture2DColorAttachement(0);
		if (!m_PingPongFBOs[i].BindAttachements())
			std::cout << "Failed to bind Ping Pong FBO " << i << std::endl;
	}	
	m_QuadRenderer.Init();
	m_BlurShader.CreateShaderProgram();
}

BlurPassOutput BlurPass::ExecuteRenderPass(LightingPassOutput lightingPassOutput, int nbHorizontalBlur, int nbVerticalBlur)
{
	bool firstIteration = true;
	int indexFBOToWrite = 0;

	FrameBuffer& writeFBO = m_PingPongFBOs[indexFBOToWrite];
	FrameBuffer& readFBO = m_PingPongFBOs[1 - indexFBOToWrite];

	m_BlurShader.Use(true);
	m_BlurShader.LoadHorizontalUniform(true);

	for (int i = 0; i < nbHorizontalBlur; i++)
	{
		indexFBOToWrite = 1 - indexFBOToWrite;
		writeFBO = m_PingPongFBOs[indexFBOToWrite];
		readFBO = m_PingPongFBOs[1 - indexFBOToWrite];

		writeFBO.Bind(true);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, firstIteration ? lightingPassOutput.outputFramebuffer.GetColorTexture(1) : readFBO.GetColorTexture(0));
		m_QuadRenderer.Render();
		writeFBO.Bind(false);

		firstIteration = false;
	}

	m_BlurShader.LoadHorizontalUniform(false);
	for (int i = 0; i < nbVerticalBlur; i++)
	{
		indexFBOToWrite = 1 - indexFBOToWrite;
		writeFBO = m_PingPongFBOs[indexFBOToWrite];
		readFBO = m_PingPongFBOs[1 - indexFBOToWrite];

		writeFBO.Bind(true);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, firstIteration ? lightingPassOutput.outputFramebuffer.GetColorTexture(1) : readFBO.GetColorTexture(0));
		m_QuadRenderer.Render();
		writeFBO.Bind(false);

		firstIteration = false;
	}

	m_BlurShader.Use(false);

	BlurPassOutput output = { writeFBO };
	return output;
}

void BlurPass::CleanUp()
{
	for (FrameBuffer& fbo : m_PingPongFBOs)
	{
		fbo.CleanUp();
	}

	m_BlurShader.CleanUp();
}
