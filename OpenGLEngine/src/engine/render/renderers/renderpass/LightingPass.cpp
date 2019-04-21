#include "LightingPass.h"
#include <iostream>

LightingPass::LightingPass()
	: m_LightingFB{1080, 720},
	m_GameObjectRenderer{},
	m_ParticuleRender{},
	m_LightRenderer{}
{
}

LightingPass::~LightingPass()
{
}

void LightingPass::Create()
{
	
	m_LightingFB.Init();
	m_LightingFB.AddTexture2DColorAttachement(0);	// HDR buffer
	m_LightingFB.AddTexture2DColorAttachement(1);	// Brightness buffer
	m_LightingFB.AddRBODepthStencilAttachement();
	if (!m_LightingFB.BindAttachements())
		std::cout << "Failed to bind shadow FBO" << std::endl;

	m_GameObjectRenderer.Init();
	m_ParticuleRender.Init();
	m_LightRenderer.Init();
}

LightingPassOutput LightingPass::ExecuteRenderPass(std::vector<GameObject>& gameObjects, std::vector<ParticuleSystem>& particuleSystems,
									 LightScene & lightScene, Camera & camera, ShadowmapPassOutput& shadowMapOutput, float frameTime)
{
	m_LightingFB.Bind(true);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_GameObjectRenderer.Render(gameObjects, lightScene, camera, shadowMapOutput);
	m_ParticuleRender.Render(particuleSystems, lightScene, camera, frameTime);
	m_LightRenderer.Render(lightScene, camera);

	m_LightingFB.Bind(false);

	LightingPassOutput lightingOutput{ m_LightingFB };
	return lightingOutput;
}

void LightingPass::CleanUp()
{
	m_GameObjectRenderer.CleanUp();
	m_ParticuleRender.CleanUp();
	m_LightRenderer.CleanUp();

	m_LightingFB.CleanUp();
}
