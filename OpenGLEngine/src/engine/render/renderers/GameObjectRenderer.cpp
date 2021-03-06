#include "GameObjectRenderer.h"
#include "../maths/Transformations.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "./MasterRenderer.h"

#pragma region Public API

GameObjectRenderer::GameObjectRenderer()
	: m_GameObjectShader{}
{
}

GameObjectRenderer::~GameObjectRenderer()
{
}

void GameObjectRenderer::Init()
{
	m_GameObjectShader.CreateShaderProgram();
}

void GameObjectRenderer::Render(std::vector<GameObject>& gameObjects, LightScene& lightScene, Camera& camera, ShadowmapPassOutput& shadowMapOutput)
{
	m_GameObjectShader.Use(true);

	glm::mat4 projectionMatrix(Transformations::GetProjectionMatrix(MasterRenderer::FOV, MasterRenderer::nearPlane, MasterRenderer::farPlane));
	glm::mat4 viewMatrix(Transformations::GetViewMatrix(camera));

	glm::mat4 lightSpaceMatrix = shadowMapOutput.directionalLightViewProjMatrix;
	glm::mat4 modelMatrix;

	for (auto& gameObject : gameObjects)
	{
		Material material(gameObject.GetMaterial());
		modelMatrix = Transformations::GetModelMatrix(gameObject.GetPosition(), gameObject.GetRotation(), gameObject.GetScale());

		if (material.IsTextured())
		{
			glActiveTexture(material.GetTexture().GetActiveTexture());
			glBindTexture(GL_TEXTURE_2D, material.GetTexture().GetTextureID());
		}

		// Load shadow map
		if (lightScene.GetDirectionalLight().GetIntensity() > 0 && lightScene.GetDirectionalLight().IsCastingShadow())
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, shadowMapOutput.shadowmapFramebuffer.GetDepthTexture());
		}

		m_GameObjectShader.LoadMatricesUniforms(modelMatrix, viewMatrix, projectionMatrix, lightSpaceMatrix);
		m_GameObjectShader.LoadLightsUniforms(lightScene, viewMatrix);
		m_GameObjectShader.LoadMaterialUniforms(material);

		gameObject.Draw();
	}

	m_GameObjectShader.Use(false);
}

void GameObjectRenderer::CleanUp()
{
	m_GameObjectShader.CleanUp();
}

#pragma endregion
