#include "ShadowmapPass.h"
#include "../../maths/Transformations.h"
#include "../MasterRenderer.h"
#include <iostream>

ShadowmapPass::ShadowmapPass()
	:m_ShadowMapShader(),
	m_ShadowMapFB{ 1080, 720 }
{
}

ShadowmapPass::~ShadowmapPass()
{
}

void ShadowmapPass::Create()
{
	m_ShadowMapFB.Init();
	m_ShadowMapFB.AddTexture2DDepthAttachement();
	if (!m_ShadowMapFB.BindAttachements())
		std::cout << "Failed to bind shadow FBO" << std::endl;

	m_ShadowMapShader.CreateShaderProgram();
}

void ShadowmapPass::GenerateShadowMap(std::vector<GameObject>& gameObjects, LightScene& lightScene)
{
	// Render the scene to a depth texture
	m_ShadowMapFB.Bind(true);
	glClear(GL_DEPTH_BUFFER_BIT);
	m_ShadowMapShader.Use(true);
	glm::mat4 lightSpaceMatrix = Transformations::GetLightSpaceMatrix(lightScene.GetDirectionalLights()[0], MasterRenderer::nearPlane, MasterRenderer::farPlane);
	glm::mat4 modelMatrix;

	// Game objects
	for (auto& gameObject : gameObjects)
	{
		Material material(gameObject.GetMaterial());
		modelMatrix = Transformations::GetModelMatrix(gameObject.GetPosition(), gameObject.GetRotation(), gameObject.GetScale());
		m_ShadowMapShader.LoadUniforms(lightSpaceMatrix, modelMatrix);
		gameObject.Draw();
	}

	m_ShadowMapShader.Use(false);
	m_ShadowMapFB.Bind(false);
}

GLuint ShadowmapPass::GetShadowmap()
{
	return m_ShadowMapFB.GetDepthTexture();
}

void ShadowmapPass::CleanUp()
{
	m_ShadowMapShader.CleanUp();
	m_ShadowMapFB.CleanUp();
}