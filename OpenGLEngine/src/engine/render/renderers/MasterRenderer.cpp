#include "MasterRenderer.h"
#include <iostream>
#include "../maths/Transformations.h"
#include "renderpass/RenderPassOutput.h"


#pragma region Public API

MasterRenderer::MasterRenderer()
	:m_ShadowmapPass{},
	m_LightingPass{},
	m_HDRGammaPass{}
{
}

MasterRenderer::~MasterRenderer()
{
}

void MasterRenderer::Init()
{
	m_ShadowmapPass.Create();
	m_LightingPass.Create();
	m_HDRGammaPass.Create();
}

void MasterRenderer::Render(std::vector<GameObject>& gameObjects, std::vector<ParticuleSystem>& particuleSystems,
							LightScene & lightScene, Camera & camera, float frameTime)
{
	// Shadowmap pass doesnt take in account particules for now...
	 ShadowmapPassOutput shadowPassOutput = m_ShadowmapPass.GenerateUnidirectionalShadowMap(gameObjects, lightScene, camera);

	// Lighting pass
	 LightingPassOutput lightingPassOutput = m_LightingPass.ExecuteRenderPass(gameObjects, particuleSystems, lightScene, camera, shadowPassOutput, frameTime);

	 // Post processing
	 m_HDRGammaPass.ExecuteRenderPass(lightingPassOutput);
}

void MasterRenderer::CleanUp()
{
	m_ShadowmapPass.CleanUp();
	m_LightingPass.CleanUp();
	m_HDRGammaPass.CleanUp();
}

#pragma endregion
