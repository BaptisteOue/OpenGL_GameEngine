#pragma once

#include "RenderPassOutput.h"
#include "../../shaders/classes/HDRGammaShader.h"

class HDRGammaCorrectionPass
{
private:

	GLfloat m_Vertices[16] = {
		// Positions	// TexCoords
		-1.0f, 1.0f,	0.0f, 1.0f,		
		-1.0f, -1.0f,	0.0f, 0.0f,
		1.0f, 1.0f,		1.0f, 1.0f,
		1.0f, -1.0f,	1.0f, 0.0f
	};

	GLuint m_QuadVAO;
	HDRGammaShader m_HDRGammaShader;
public:
	HDRGammaCorrectionPass();
	~HDRGammaCorrectionPass();

	void Create();
	void ExecuteRenderPass(LightingPassOutput lightingPassOutput);
	void CleanUp();
};