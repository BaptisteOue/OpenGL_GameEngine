#pragma once

#include "RenderPassOutput.h"
#include "../../shaders/classes/BloomGammaHDRShader.h"
#include "../../framebuffers/FrameBuffer.h"
#include "../../renderers/QuadRenderer.h"

class BloomGammaHDRPass
{
private:

	QuadRenderer m_QuadRenderer;
	BloomGammaHDRShader m_BloomGammaHDRShader;

public:
	BloomGammaHDRPass();
	~BloomGammaHDRPass();

	void Create();
	void ExecuteRenderPass(LightingPassOutput lightingPassOutput, BlurPassOutput bloomPassOutput);
	void CleanUp();
};