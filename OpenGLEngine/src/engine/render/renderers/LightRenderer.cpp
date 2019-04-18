#include "LightRenderer.h"
#include "../maths/Transformations.h"
#include "MasterRenderer.h"

LightRenderer::LightRenderer()
	: m_LightShader{}
{
}

LightRenderer::~LightRenderer()
{
}

void LightRenderer::Init()
{
	m_LightShader.CreateShaderProgram();
}

void LightRenderer::Render(const LightScene& lightScene, Camera& camera)
{

	glm::mat4 modelMatrix;
	glm::mat4 viewMatrix{ Transformations::GetViewMatrix(camera) };
	glm::mat4 projectionMatrix{ Transformations::GetProjectionMatrix(MasterRenderer::FOV, MasterRenderer::nearPlane, MasterRenderer::farPlane) };

	m_LightShader.Use(true);

	for (auto lightObject : lightScene.GetDebugLightObjects())
	{
		modelMatrix = Transformations::GetModelMatrix(lightObject.GetPosition(), lightObject.GetRotation(), lightObject.GetScale());
		m_LightShader.LoadMatricesUniforms(modelMatrix, viewMatrix, projectionMatrix);
		m_LightShader.LoadColorUniform(lightObject.GetMaterial().GetKa());
		lightObject.Draw();
	}

	m_LightShader.Use(false);
}

void LightRenderer::CleanUp()
{
	m_LightShader.CleanUp();
}
