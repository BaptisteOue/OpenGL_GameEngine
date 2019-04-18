#pragma once

#include "RenderPassOutput.h"
#include "../../shaders/classes/PostProcessingShader.h"

class PostProcessing
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
	PostProcessingShader m_PPShader;
public:
	PostProcessing();
	~PostProcessing();

	void Create();
	void ExecuteRenderPass(LightingPassOutput lightingPassOutput);
	void CleanUp();
};