#include "GameObjectRenderer.h"
#include "../maths/Transformations.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

#pragma region Public API

GameObjectRenderer::GameObjectRenderer()
	: m_TesselatedShader{},
	m_ShadowMapShader{},
	m_TestShader{ "./src/engine/render/shaders/src/vertexShaderTEST.glsl",
					"./src/engine/render/shaders/src/fragmentShaderTEST.glsl" },
	m_ShadowMapFB{1080, 720}
{
}

GameObjectRenderer::~GameObjectRenderer()
{
}

void GameObjectRenderer::Init()
{
	m_TesselatedShader.CreateShaderProgram();
	m_ShadowMapShader.CreateShaderProgram();
	m_TestShader.CreateShaderProgram();

	m_ShadowMapFB.Init();
	m_ShadowMapFB.AddTexture2DDepthAttachement();
	if (!m_ShadowMapFB.BindAttachements())
		std::cout << "failed to fbo" << std::endl;

	float quadVertices[] = {
		// positions   // texCoords
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 -1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};

	glGenVertexArrays(1, &m_QuadVAO);
	glBindVertexArray(m_QuadVAO);
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
}

void GameObjectRenderer::Render(std::vector<GameObject>& gameObjects, LightScene& lightScene, Camera& camera)
{
	// ShadowMap pass
	ShadowMapPass(gameObjects, lightScene, camera);
	
	// Then render
	//RenderPass(gameObjects, lightScene, camera);
}

void GameObjectRenderer::CleanUp()
{
	m_TesselatedShader.CleanUp();
}

#pragma endregion


#pragma region Private API

void GameObjectRenderer::ShadowMapPass(std::vector<GameObject>& gameObjects, LightScene& lightScene, Camera& camera)
{

	m_ShadowMapFB.Bind(true);
	glClear(GL_DEPTH_BUFFER_BIT);

	m_ShadowMapShader.Use(true);
	glm::mat4 lightSpaceMatrix = Transformations::GetLightSpaceMatrix(lightScene.GetDirectionalLights()[0], nearPlane, farPlane);
	glm::mat4 modelMatrix;
	for (auto& gameObject : gameObjects)
	{
		Material material(gameObject.GetMaterial());
		modelMatrix = Transformations::GetModelMatrix(gameObject.GetPosition(), gameObject.GetRotation(), gameObject.GetScale());
		m_ShadowMapShader.LoadUniforms(lightSpaceMatrix, modelMatrix);
		gameObject.Draw();
	}
	m_ShadowMapShader.Use(false);
	m_ShadowMapFB.Bind(false);


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_TestShader.Use(true);
		glDisable(GL_DEPTH_TEST);
			glBindVertexArray(m_QuadVAO);
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, m_ShadowMapFB.GetDepthTexture());
				glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
			glBindVertexArray(0);
		glEnable(GL_DEPTH_TEST);
	m_TestShader.Use(false);
}

void GameObjectRenderer::RenderPass(std::vector<GameObject>& gameObjects, LightScene& lightScene, Camera& camera)
{
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

#pragma endregion
