#include "MasterRenderer.h"
#include <iostream>
#include "../maths/Transformations.h"
#include "renderpass/RenderPassOutput.h"


#pragma region Public API

MasterRenderer::MasterRenderer()
	:m_ShadowmapPass{},
	m_LightingPass{},
	m_GammaBloomHDRPass{},
	m_BlurPass{},
	m_PolygonMode{GL_FILL}
{
}

MasterRenderer::~MasterRenderer()
{
}

void MasterRenderer::Init()
{
	m_ShadowmapPass.Create();
	m_LightingPass.Create();
	m_GammaBloomHDRPass.Create();
	m_BlurPass.Create();
}

void MasterRenderer::SetPolygonMode(GLuint polygonMode)
{
	m_PolygonMode = polygonMode;
}

void MasterRenderer::Render(std::vector<GameObject>& gameObjects, std::vector<ParticuleSystem>& particuleSystems,
							LightScene & lightScene, Camera & camera, float frameTime)
{
	// Shadowmap pass doesnt take in account particules for now...
	ShadowmapPassOutput shadowPassOutput = m_ShadowmapPass.GenerateUnidirectionalShadowMap(gameObjects, lightScene, camera);

	// Lighting pass
	glPolygonMode(GL_FRONT_AND_BACK, m_PolygonMode);
	LightingPassOutput lightingPassOutput = m_LightingPass.ExecuteRenderPass(gameObjects, particuleSystems, lightScene, camera, shadowPassOutput, frameTime);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Blur pass
	BlurPassOutput blurPassOutput = m_BlurPass.ExecuteRenderPass(lightingPassOutput, 10, 10);

	// Bloom, Gamma and HDR pass
	m_GammaBloomHDRPass.ExecuteRenderPass(lightingPassOutput, blurPassOutput);
}

void MasterRenderer::CleanUp()
{
	m_ShadowmapPass.CleanUp();
	m_LightingPass.CleanUp();
	m_GammaBloomHDRPass.CleanUp();
	m_BlurPass.CleanUp();
}

#pragma endregion
