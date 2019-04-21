#pragma once

#include "RenderPassOutput.h"
#include "../../shaders/classes/BlurShader.h"
#include "../../framebuffers/FrameBuffer.h"
#include "../../renderers/QuadRenderer.h"

class BlurPass
{

private:
	BlurShader m_BlurShader;
	FrameBuffer m_PingPongFBOs[2];
	QuadRenderer m_QuadRenderer;

public:
	BlurPass();
	~BlurPass();

	void Create();
	BlurPassOutput ExecuteRenderPass(LightingPassOutput lightingPassOutput, int nbHorizontalBlur = 1, int nbVerticalBlur = 1);
	void CleanUp();
};