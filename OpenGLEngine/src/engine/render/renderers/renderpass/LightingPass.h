#pragma once

#include "../../framebuffers/FrameBuffer.h"
#include "../../shaders/classes/BasicShader.h"
#include "../../renderers/GameObjectRenderer.h"
#include "../../renderers/ParticuleRender.h"
#include "../../renderers/SkyboxRenderer.h"
#include "../../renderers/LightRenderer.h"
#include "RenderPassOutput.h"


class LightingPass
{
private:
	ParticuleRender m_ParticuleRender;
	GameObjectRenderer m_GameObjectRenderer;
	SkyboxRenderer m_SkyboxRenderer;
	LightRenderer m_LightRenderer;

	FrameBuffer m_LightingFB;

public:
	LightingPass();
	~LightingPass();

	void Create();
	LightingPassOutput ExecuteRenderPass(std::vector<GameObject>& gameObjects, std::vector<ParticuleSystem>& particuleSystems,
										 LightScene & lightScene, Camera & camera, ShadowmapPassOutput& shadowMapOutput, float frameTime);
	void CleanUp();

};