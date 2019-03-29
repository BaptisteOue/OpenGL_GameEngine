#include "GameObjectRenderer.h"
#include "../maths/Transformations.h"

#pragma region Public API

GameObjectRenderer::GameObjectRenderer()
	: m_BasicShader{}, m_TesselatedShader{}
{
}

GameObjectRenderer::~GameObjectRenderer()
{
}

void GameObjectRenderer::Init()
{
	m_TesselatedShader.CreateShaderProgram();
	m_BasicShader.CreateShaderProgram();
}

void GameObjectRenderer::Render(std::vector<GameObject>& gameObjects, LightScene& lightScene, Camera& camera)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_TesselatedShader.Use(true);

	glm::mat4 projectionMatrix(Transformations::GetProjectionMatrix(FOV, nearPlane, farPlane));
	glm::mat4 viewMatrix(Transformations::GetViewMatrix(camera));
	glm::mat4 modelMatrix;

	for (auto& gameObject : gameObjects)
	{
		Material material(gameObject.GetMaterial());

		if (material.IsTextured())
		{
			glActiveTexture(material.GetTexture().GetActiveTexture());
			glBindTexture(GL_TEXTURE_2D, material.GetTexture().GetTextureID());
		}

		modelMatrix = Transformations::GetModelMatrix(gameObject.GetPosition(), gameObject.GetRotation(), gameObject.GetScale());

		m_TesselatedShader.LoadTessLevels(gameObject.GetTessLevelOuter(), gameObject.GetTessLevelInner());
		m_TesselatedShader.LoadMatricesUniforms(modelMatrix, viewMatrix, projectionMatrix);
		m_TesselatedShader.LoadLightsUniforms(lightScene, viewMatrix);
		m_TesselatedShader.LoadMaterialUniforms(material);

		gameObject.DrawTesselated();
	}

	m_TesselatedShader.Use(false);
}

void GameObjectRenderer::CleanUp()
{
	m_TesselatedShader.CleanUp();
}

#pragma endregion


