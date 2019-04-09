#include "LightingPass.h"

LightingPass::LightingPass()
	: m_GameObjectRenderer{},
	m_ParticuleRender{}
{
}

LightingPass::~LightingPass()
{
}

void LightingPass::ExecuteRenderPass(std::vector<GameObject>& gameObjects, std::vector<ParticuleSystem>& particuleSystems, 
									 LightScene & lightScene, Camera & camera, GLuint shadowMap, float frameTime)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_GameObjectRenderer.Render(gameObjects, lightScene, camera, shadowMap);

	m_ParticuleRender.Render(particuleSystems, lightScene, camera, frameTime);
}

void LightingPass::Create()
{
	m_GameObjectRenderer.Init();
	m_ParticuleRender.Init();
}

void LightingPass::CleanUp()
{
	m_GameObjectRenderer.CleanUp();
	m_ParticuleRender.CleanUp();
}
