#include "MasterRenderer.h"
#include <iostream>
#include "../maths/Transformations.h"


#pragma region Public API

MasterRenderer::MasterRenderer()
	: m_GameObjectRender(),
	m_ParticuleRender(),
	m_ShadowMapShader(),
	m_ShadowMapFB{ 1080, 720 }
{
}

MasterRenderer::~MasterRenderer()
{
}

void MasterRenderer::Init()
{
	// TODO : make a "render pass" mechanism
	// For now just had a framebuffer and shadow shader for shadow mapping
	m_ShadowMapFB.Init();
	m_ShadowMapFB.AddTexture2DDepthAttachement();
	if (!m_ShadowMapFB.BindAttachements())
		std::cout << "failed to fbo" << std::endl;

	m_ShadowMapShader.CreateShaderProgram();

	m_GameObjectRender.Init();
	//m_ParticuleRender.Init();
}

void MasterRenderer::Render(std::vector<GameObject>& gameObjects,
	std::vector<ParticuleSystem>& particuleSystems,
	LightScene & lightScene,
	Camera & camera,
	float frameTime)
{

	glEnable(GL_CULL_FACE);

	// Render to shadow map
	//glCullFace(GL_FRONT);
	ShadowMapPass(gameObjects, particuleSystems, lightScene, camera);

	// Then render game object using the shadow map
	//glCullFace(GL_BACK);
	m_GameObjectRender.Render(gameObjects, lightScene, camera, m_ShadowMapFB.GetDepthTexture());

	//m_ParticuleRender.Render(particuleSystems, lightScene, camera, m_ShadowMapFB.GetDepthTexture(), frameTime);
}

void MasterRenderer::CleanUp()
{
	m_GameObjectRender.CleanUp();
	m_ParticuleRender.CleanUp();

	m_ShadowMapFB.CleanUp();
	m_ShadowMapShader.CleanUp();
}

#pragma endregion

#pragma region Private API

void MasterRenderer::ShadowMapPass(std::vector<GameObject>& gameObjects, 
								   std::vector<ParticuleSystem>& particuleSystems,
								   LightScene& lightScene, 
								   Camera& camera)
{
	// Render the scene to a depth texture
	m_ShadowMapFB.Bind(true);
	glClear(GL_DEPTH_BUFFER_BIT);
	m_ShadowMapShader.Use(true);
	glm::mat4 lightSpaceMatrix = Transformations::GetLightSpaceMatrix(lightScene.GetDirectionalLights()[0], nearPlane, farPlane);
	glm::mat4 modelMatrix;

	// Game objects
	for (auto& gameObject : gameObjects)
	{
		Material material(gameObject.GetMaterial());
		modelMatrix = Transformations::GetModelMatrix(gameObject.GetPosition(), gameObject.GetRotation(), gameObject.GetScale());
		m_ShadowMapShader.LoadUniforms(lightSpaceMatrix, modelMatrix);
		gameObject.Draw();
	}

	// TODO : Shadow mapping for particules

	m_ShadowMapShader.Use(false);
	m_ShadowMapFB.Bind(false);
}

#pragma endregion
