#include "MasterRenderer.h"
#include <iostream>
#include "../maths/Transformations.h"


#pragma region Public API

MasterRenderer::MasterRenderer()
	:m_ShadowmapPass{},
	m_LightingPass{}
{
}

MasterRenderer::~MasterRenderer()
{
}

void MasterRenderer::Init()
{
	m_ShadowmapPass.Create();
	m_LightingPass.Create();
}

void MasterRenderer::Render(std::vector<GameObject>& gameObjects, std::vector<ParticuleSystem>& particuleSystems,
							LightScene & lightScene, Camera & camera, float frameTime)
{
	// Shadowmap pass doesnt take in account particules for now...
	m_ShadowmapPass.GenerateUnidirectionalShadowMap(gameObjects, lightScene, camera);

	// Lighting pass
	m_LightingPass.ExecuteRenderPass(gameObjects, particuleSystems, lightScene, camera, m_ShadowmapPass.GetUnidirectionalShadowmap(), frameTime);
}

void MasterRenderer::CleanUp()
{
	m_ShadowmapPass.CleanUp();
	m_LightingPass.CleanUp();
}

#pragma endregion
